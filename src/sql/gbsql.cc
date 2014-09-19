#include "gbsql.h"

#include <iostream>

using namespace std;

#include <wx\wxsqlite3.h>

GBSql::GBSql() {
    if (InitializeDatabase()) {

    } 
}

GBSql::~GBSql() {

}

void GBSql::Close() {
    m_db.Close();
}

int GBSql::InsertCourse(const Course &c) {
    int ret = -1;
    static const char* sqlCommand = "INSERT INTO courses (\
                                    cid,    \
                                    title,  \
                                    start,  \
                                    end) VALUES (?1, ?2, ?3, ?4)";

    try {
        wxSQLite3Statement smt = m_db.PrepareStatement(sqlCommand);

        smt.Bind(1, *c.GetId());
        smt.Bind(2, *c.GetTitle());
        smt.Bind(3, c.GetStart()->Format("%x"));
        smt.Bind(4, c.GetEnd()->Format("%x"));

        ret = smt.ExecuteUpdate();
    } catch (wxSQLite3Exception &e) {
        cout << e.GetMessage() << endl;
    }

    return ret;
}

bool GBSql::InitializeDatabase() {
    const char* sqlCommands[] = {
        "CREATE TABLE IF NOT EXISTS courses (\
            cid     TEXT    not null,\
            title   TEXT    not null,\
            start   TEXT    not null,\
            end     TEXT    not null,\
            primary key(cid));",
        NULL };

    int i = 0;

    try {
        m_db.Open(wxT("gb.db"));

        while (sqlCommands[i] != NULL) {
            m_db.ExecuteUpdate(sqlCommands[i++]);
        }
    } catch (wxSQLite3Exception &e) {
        cout << e.GetMessage() << endl;

        return false;
    }

    return true;
}
