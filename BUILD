
Here are some notes on how to make it all work in different configurations.


-- Autogenerated scripts for your test database.

When configuring your build, specify the connection to the test database,
also specify the SQL dialect.  This will help generate proper
DDL scripts.

$ ./configure --with-test-dbtype=MYSQL --with-test-db=test1_db \
    --with-test-user=test1 --with-test-passwd=test1_pwd 

After running ./configure and make commands you will find the
autogenerated scripts for your test database here:

lib/orm/test/mk_tables.sql
examples/domain/mk_tables.sql


-- How to set up empty test database and test user.
Here are necessary steps to take to create an empty database schema
where to put the autogenerated DDL scripts.

:: For MySQL ::
You should know the root password for your MySQL database to be able
to manage databases and users.

$ mysql -u root -p mysql
Enter password: 
Reading table information for completion of table and column names
You can turn off this feature to get a quicker startup with -A

Welcome to the MySQL monitor.  Commands end with ; or \g.
Your MySQL connection id is 41
Server version: 5.1.41-3ubuntu12.10 (Ubuntu)

Type 'help;' or '\h' for help. Type '\c' to clear the current input statement.

mysql> create database test1_db default charset utf8;
Query OK, 1 row affected (0.00 sec)

mysql> create user test1 identified by "test1_pwd";
Query OK, 0 rows affected (0.00 sec)

mysql> grant all on test1_db.* to test1;
Query OK, 0 rows affected (0.00 sec)

mysql> exit
Bye
$ mysql -u test1 -ptest1_pwd test1_db < lib/orm/test/mk_tables.sql
$ mysql -u test1 -ptest1_pwd test1_db < examples/domain/mk_tables.sql

:: For FireBird (InterBase may also apply) ::
There is default SYSDBA password: masterkey

$ gsec -user SYSDBA -password masterkey
GSEC> add test1 -pw test1_pwd
Warning - maximum 8 significant bytes of password used
GSEC> quit

$ isql-fb
Use CONNECT or CREATE DATABASE to specify a database
SQL> CREATE DATABASE '/var/lib/firebird/2.0/data/test1_db.fdb'
CON> page_size 8192 user 'test1' password 'test1_pwd';
SQL> quit;
$ isql-fb -u test1 -p test1_pwd \
  localhost:/var/lib/firebird/2.0/data/test1_db.fdb < lib/orm/test/mk_tables.sql
$ isql-fb -u test1 -p test1_pwd \
  localhost:/var/lib/firebird/2.0/data/test1_db.fdb < examples/domain/mk_tables.sql


-- How to build the library under Windows
For now it is possible to build the framework using MinGW/MSYS toolchain.
Just apply the usual autogen.sh/configure/make/make check/make install
The build is tested with libxml2-2.7.7, cppunit-1.12.1, boost-1.38.0.
When configuring libxml2 and cppunit be sure to specify --prefix=/mingw.
Specify your boost build location like this:
$ ./configure --with-boost-includes=c:/build-yborm/boost_1_38_0 \
  --with-boost-libs=c:/build-yborm/boost_1_38_0/stage/lib ...

There is work in progress to make yborm build with cmake and to port it
to MS Visual C++ and Borland C++ Builder compilers.


-- Example1
Yes, there are not too many examples and docs.  This will be fixed
in future.
If you wonder what example1 should produce on stdout here is sample
(for MySQL).

$ sh example1.sh 
Enter name, email: 
Vaclav vaclav@yandex.ru
Enter order amount: 
234.56
Mon Oct 10 11:10:14 2011: prepare: INSERT INTO T_CLIENT (DT, EMAIL, IS_AGENCY, NAME, PHONE, URL) VALUES (?, ?, ?, ?, ?, ?)
Mon Oct 10 11:10:14 2011: exec prepared: p1="'2011-10-10 11:10:00'" p2="'vaclav@yandex.ru'" p3="0" p4="'Vaclav'" p5="NULL" p6="NULL"
Mon Oct 10 11:10:14 2011: exec_direct: SELECT LAST_INSERT_ID() LID
Mon Oct 10 11:10:14 2011: fetch: LID='34' 
Mon Oct 10 11:10:14 2011: fetch: no more rows
Mon Oct 10 11:10:14 2011: prepare: INSERT INTO T_ORDER (CLIENT_ID, DT, RECEIPT_DT, RECEIPT_SUM, TOTAL_SUM) VALUES (?, ?, ?, ?, ?)
Mon Oct 10 11:10:14 2011: exec prepared: p1="34" p2="'2011-10-10 11:10:07'" p3="NULL" p4="0" p5="234.56"
Mon Oct 10 11:10:14 2011: exec_direct: SELECT LAST_INSERT_ID() LID
Mon Oct 10 11:10:14 2011: fetch: LID='45' 
Mon Oct 10 11:10:14 2011: fetch: no more rows
client created: 34
order created: 45
Mon Oct 10 11:10:14 2011: commit
Mon Oct 10 11:10:14 2011: prepare: SELECT ID, DT, RECEIPT_SUM, RECEIPT_DT, CLIENT_ID, TOTAL_SUM FROM T_ORDER WHERE 1=1 AND ID = ?
Mon Oct 10 11:10:14 2011: exec prepared: p1="45"
Mon Oct 10 11:10:14 2011: fetch: CLIENT_ID='34' DT='2011-10-10 11:10:07' ID='45' RECEIPT_DT='2011-10-10 11:10:14' RECEIPT_SUM='0.000000' TOTAL_SUM='234.560000' 
Mon Oct 10 11:10:14 2011: fetch: no more rows
Mon Oct 10 11:10:14 2011: prepare: SELECT ID, DT, NAME, EMAIL, PHONE, URL, IS_AGENCY FROM T_CLIENT WHERE 1=1 AND ID = ?
Mon Oct 10 11:10:14 2011: exec prepared: p1="34"
Mon Oct 10 11:10:14 2011: fetch: DT='2011-10-10 11:10:00' EMAIL='vaclav@yandex.ru' ID='34' IS_AGENCY='0' NAME='Vaclav' PHONE=NULL URL=NULL 
Mon Oct 10 11:10:14 2011: fetch: no more rows
<order><id>45</id><dt>2011-10-10T11:10:07</dt><receipt-sum>0</receipt-sum><receipt-dt>2011-10-10T11:10:14</receipt-dt><owner><id>34</id><dt>2011-10-10T11:10:00</dt><name>Vaclav</name><email>vaclav@yandex.ru</email><phone is_null="1"/><url is_null="1"/><agency-flag>0</agency-flag></owner><total-sum>234.56</total-sum></order>

Mon Oct 10 11:10:14 2011: rollback
$ 
