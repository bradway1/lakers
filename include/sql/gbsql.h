#ifndef _GBSQL_H
#define _GBSQL_H

#include "data/course.h"
#include "data/student.h"
#include "data/assessment.h"

#include <wx/wxsqlite3.h>

#include <vector>

using std::vector;

class GBSql {
    public:
        GBSql();
        ~GBSql();

        void Close();

        int InsertCourse(const Course &);
        int UpdateCourse(const Course &);
        int DeleteCourse(const Course &);
        int SelectCourse(vector<Course*> *);

        int InsertStudent(const Student &);
        int UpdateStudent(const Student &);
        int DeleteStudent(const Student &);
        int SelectStudents(vector<Student*> *);

        int AddStudentCourseRelation(const Student &, const Course &);

        int InsertAssessment(const Assessment &);
        int UpdateAssessment(const Assessment &);
        int DeleteAssessment(const Assessment &);
        int SelectAssessments(vector<Assessment*> *);

    private:
        wxSQLite3Database m_db;

        bool InitializeDatabase();
};

#endif
