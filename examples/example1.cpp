#include <memory>
#include <iostream>
#include <orm/Session.h>
#include <orm/SqlDataSource.h>
#include <orm/MetaDataSingleton.h>
#include <orm/XMLMetaDataConfig.h>
#include "domain/Client.h"
#include "domain/Order.h"
//#define HAVE_DBPOOL3
#ifdef HAVE_DBPOOL3
#include <orm/DBPoolDriver.h>
#endif

using namespace std;

int main()
{
    Yb::load_meta("DBScheme.xml", Yb::theMetaData::instance());
#ifdef HAVE_DBPOOL3
    std::auto_ptr<Yb::DBPoolConfig> conf(
            new Yb::DBPoolConfig("dbpool.cfg.xml"));
    std::auto_ptr<Yb::SqlDriver> drv(
            new Yb::DBPoolDriver(conf, "MY_DBPOOL"));
    Yb::register_sql_driver(drv);
    std::auto_ptr<Yb::SqlConnect> conn(
            new Yb::SqlConnect("MY_DBPOOL", "MYSQL", "default"));
    Yb::Engine engine(Yb::Engine::MANUAL, conn);
#else
    Yb::Engine engine(Yb::Engine::MANUAL);
#endif
    Yb::Session session(Yb::theMetaData::instance(),
            std::auto_ptr<Yb::DataSource>(
                new Yb::SqlDataSource(Yb::theMetaData::instance(), engine)));
    engine.get_connect()->set_echo(true);
    Domain::Client client(session);
    string name, email;
    cout << "Enter name, email: \n";
    cin >> name >> email;
    client.set_name(name);
    client.set_email(email);
    client.set_dt(Yb::now());
    Domain::Order order(session);
    string value;
    cout << "Enter order amount: \n";
    cin >> value;
    order.set_total_sum(Yb::Decimal(value));
    order.set_client(client);
    session.flush();
    cout << "client created: " << client.get_id().as_longint() << endl;
    cout << "order created: " << order.get_id().as_longint() << endl;
    engine.commit();
    cout << order.auto_xmlize(1).get_xml() << endl;
    return 0;
}
// vim:ts=4:sts=4:sw=4:et:
