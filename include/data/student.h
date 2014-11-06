#ifndef _STUDENT_H
#define _STUDENT_H

#include <vector>

using std::vector;

#include <wx/string.h>

#include "data/grade.h"

class Student {
  public:
    Student();
    Student(const wxString &id);
    ~Student();

    wxString &Id() const { return *m_pId; }
    wxString &First() const { return *m_pFirst; }
    wxString &Last() const { return *m_pLast; }

    void SetFirst(const wxString &first) { m_pFirst = new wxString(first); }
    void SetLast(const wxString &last) { m_pLast = new wxString(last); }

    void AddGrade(Grade *grade);
    Grade &GetGrade(int index) const;
    int GradeCount();

    void Clear() { m_grades.clear(); }

  private:
    wxString *m_pId; 
    wxString *m_pFirst;
    wxString *m_pLast;
    vector<Grade*> m_grades;
};

#endif
