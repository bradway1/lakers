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

int GBSql::UpdateCourse(const Course &c) { 
    int ret = -1;
    static const char* sqlCommand = "UPDATE courses SET \
                                     title=?1,  \
                                     start=?2,  \
                                     end=?3     \
                                     WHERE cid=?4";
    
    try {
        wxSQLite3Statement smt = m_db.PrepareStatement(sqlCommand);

        smt.Bind(1, *c.GetTitle());
        smt.Bind(2, c.GetStart()->Format("%x"));
        smt.Bind(3, c.GetEnd()->Format("%x"));
        smt.Bind(4, *c.GetId());

        ret = smt.ExecuteUpdate();
    } catch (wxSQLite3Exception &e) {
        cout << e.GetMessage() << endl;
    }

    return ret;
}

int GBSql::DeleteCourse(const Course &c) {
    int ret = -1;
    static const char* sqlCommand = "DELETE FROM courses WHERE cid=?1";
    
    try {
        wxSQLite3Statement smt = m_db.PrepareStatement(sqlCommand);

        smt.Bind(1, *c.GetId());

        ret = smt.ExecuteUpdate();
    } catch (wxSQLite3Exception &e) {
        cout << e.GetMessage() << endl;
    }

    return ret;
}

int GBSql::SelectCourse(vector<Course*> *cVec) {
    int ret = -1;

    static const char* sqlCommand = "SELECT * FROM courses";

    try {
        wxSQLite3Statement smt = m_db.PrepareStatement(sqlCommand);

        wxSQLite3ResultSet r = smt.ExecuteQuery();

        Course *c;
        wxDateTime date;
        wxString::const_iterator end;

        while (r.NextRow()) {
            c = new Course();

            c->SetId(r.GetAsString("cid"));

            c->SetTitle(r.GetAsString("title"));

            date.ParseFormat(r.GetAsString("start"), "%x", &end);

            c->SetStart(date);

            date.ParseFormat(r.GetAsString("end"), "%x", &end);

            c->SetEnd(date);

            cVec->push_back(c);
        }

        ret = cVec->size();
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
            primary key(cid))",
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
