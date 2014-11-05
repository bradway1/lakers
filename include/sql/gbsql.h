#ifndef _GBSQL_H
#define _GBSQL_H

#include <vector>

using std::vector;

#include <wx/wxsqlite3.h>

#include "data/course.h"
#include "data/student.h"
#include "data/assessment.h"
#include "data/observer.h"

class GBSql : public Observer {
  public:
    static GBSql *Instance();

    int Initialize(const wxString &file);

    int Open(const wxString &file);
    int Close();
   
    int Import(const wxString &file, const wxString &backup); 
  
    int SelectCourses(vector<Course*> *result);  
    int InsertCourse(const Course &c);
    int DeleteCourse(const Course &c);

    int SelectStudentsByCourse(Course &c);
    int InsertStudent(const Student &s);
    int InsertStudentIntoCourse(const Student &s, const Course &c);
    int DeleteStudent(const Student &s);

    int SelectAssessmentsByCourse(Course &c);
    int InsertAssessmentIntoCourse(const Assessment &a, const Course &c);
    int DeleteAssessment(const Assessment &a);

    int SelectGradesForStudentInCourse(Student &s, const Course &c);
    int InsertGradeForStudent(const Grade &g, const Student &s, const Course &c, const Assessment &a);
    int DeleteGrade(const Grade &g);

  private:
    GBSql();

    GBSql(GBSql const &) { };
    GBSql& operator=(GBSql const&) { };

    int Update(const wxString &sql);
    wxSQLite3ResultSet *Query(const wxString &sql);

    static GBSql *m_pInstance;

    wxSQLite3Database m_db;
};

#endif
