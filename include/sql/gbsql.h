#ifndef _GBSQL_H
#define _GBSQL_H

#include "data/course.h"

#include <wx/wxsqlite3.h>

class GBSql {
    public:
        GBSql();
        ~GBSql();

        void Close();

        int InsertCourse(const Course &);

    private:
        wxSQLite3Database m_db;

        bool InitializeDatabase();
};

#endif
