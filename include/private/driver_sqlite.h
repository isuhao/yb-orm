// -*- Mode: C++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: nil; -*-
#ifndef YB__ORM__DRIVER_SQLITE__INCLUDED
#define YB__ORM__DRIVER_SQLITE__INCLUDED

#include <memory>
#include <vector>
#include "util/thread.h"
#include "orm/sql_driver.h"
#include <sqlite3.h>

namespace Yb {

typedef ::sqlite3 SQLiteDatabase;
typedef ::sqlite3_stmt SQLiteQuery;

class SQLiteCursorBackend: public SqlCursorBackend
{
    SQLiteDatabase *conn_;
    SQLiteQuery *stmt_;
    int last_code_, exec_count_;
public:
    SQLiteCursorBackend(SQLiteDatabase *conn);
    ~SQLiteCursorBackend();
    void close();
    void exec_direct(const String &sql);
    void prepare(const String &sql);
    void exec(const Values &params);
    RowPtr fetch_row();
};

class SQLiteDriver;

class SQLiteConnectionBackend: public SqlConnectionBackend
{
    SQLiteDatabase *conn_;
    SQLiteDriver *drv_;
    bool own_handle_;
public:
    SQLiteConnectionBackend(SQLiteDriver *drv);
    ~SQLiteConnectionBackend();
    void open(SqlDialect *dialect, const SqlSource &source);
    void use_raw(SqlDialect *dialect, void *raw_connection);
    void *get_raw();
    std::auto_ptr<SqlCursorBackend> new_cursor();
    void close();
    void begin_trans();
    void commit();
    void rollback();
};

class SQLiteDriver: public SqlDriver
{
    friend class SQLiteConnectionBackend;
    Mutex conn_mux_;
public:
    SQLiteDriver();
    std::auto_ptr<SqlConnectionBackend> create_backend();
    void parse_url_tail(const String &dialect_name,
            const String &url_tail, StringDict &source);
};

} //namespace Yb

// vim:ts=4:sts=4:sw=4:et:
#endif // YB__ORM__DRIVER_SQLITE__INCLUDED
