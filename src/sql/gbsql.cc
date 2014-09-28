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

int GBSql::InsertStudent(const Student &s) {
    static const char *sqlCommand = "INSERT INTO students (\
                                     sid,       \
                                     first,     \
                                     last) VALUES (?1, ?2, ?3)";
    try {
        wxSQLite3Statement smt = m_db.PrepareStatement(sqlCommand);
    
        smt.Bind(1, *s.GetStudentId());
        smt.Bind(2, *s.GetFirst());
        smt.Bind(3, *s.GetLast());

        return smt.ExecuteUpdate();
    } catch (wxSQLite3Exception &e) {
        cerr << e.GetMessage() << endl;
    
        return -1;
    }

    return 0;
}

int GBSql::UpdateStudent(const Student &s) {
    static const char *sqlCommand = "UPDATE students SET \
                                     first=?1,  \
                                     last=?2    \
                                     WHERE sid=?3";

    try {
        wxSQLite3Statement smt = m_db.PrepareStatement(sqlCommand);

        smt.Bind(1, *s.GetFirst());
        smt.Bind(2, *s.GetLast());
        smt.Bind(3, *s.GetStudentId());

        return smt.ExecuteUpdate();
    } catch (wxSQLite3Exception &e) {
        cerr << e.GetMessage() << endl;
    
        return -1;
    }

    return 0;
}

int GBSql::DeleteStudent(const Student &s) {
    static const char *sqlCommand = "DELETE FROM students \
                                     WHERE sid=?1";

    try {
        wxSQLite3Statement smt = m_db.PrepareStatement(sqlCommand);

        smt.Bind(1, *s.GetStudentId());

        return smt.ExecuteUpdate();
    } catch (wxSQLite3Exception &e) {
        cerr << e.GetMessage() << endl;
    
        return -1;
    }

    return 0;
}

int GBSql::SelectStudents(vector<Student*> *sVec) {
    static const char *sqlCommand = "SELECT * FROM students";
    
    try {
        wxSQLite3Statement smt = m_db.PrepareStatement(sqlCommand);

        wxSQLite3ResultSet r = smt.ExecuteQuery();

        Student *s;

        while (r.NextRow()) {
            s = new Student();

            s->SetStudentId(r.GetString("sid"));

            s->SetFirst(r.GetString("first"));

            s->SetLast(r.GetString("last"));

            sVec->push_back(s);
        }

        return sVec->size();
    } catch (wxSQLite3Exception &e) {
        cerr << e.GetMessage() << endl;
        
        return -1;
    }
    
    return 0;
}

int GBSql::AddStudentCourseRelation(const Student &s, const Course &c) {
    static const char *sqlCommand = "INSERT INTO sc_relation (\
                                     sid, \
                                     cid) VALUES (?1, ?2)";

    try {
        wxSQLite3Statement smt = m_db.PrepareStatement(sqlCommand);

        smt.Bind(1, *c.GetId());
        smt.Bind(2, *s.GetStudentId());

        return smt.ExecuteUpdate();
    } catch (wxSQLite3Exception &e) {
        cerr << e.GetMessage() << endl;

        return -1;
    }
    
    return 0;
}

bool GBSql::InitializeDatabase() {
    const char* sqlCommands[] = {
        "CREATE TABLE IF NOT EXISTS courses (\
            cid     TEXT    not null, \
            title   TEXT    not null, \
            start   TEXT    not null, \
            end     TEXT    not null, \
            primary key(cid))",
        "CREATE TABLE IF NOT EXISTS students (\
            sid     TEXT    not null, \
            first   TEXT    not null, \
            last    TEXT    not null, \
            primary key(sid))",
        "CREATE TABLE IF NOT EXISTS sc_relation (\
            id      INTEGER PRIMARY KEY AUTOINCREMENT, \
            sid     TEXT    not null, \
            cid     TEXT    not null)",
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
