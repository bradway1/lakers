#ifndef _COURSE_H
#define _COURSE_H

#include <vector>

using std::vector;

#include <wx/string.h>

#include "data/student.h"
#include "data/assessment.h"

class Course {
  public:
    Course();
    Course(const wxString &id);
    ~Course();

    wxString &Id() const { return *m_pId; }
    wxString &Title() const { return *m_pTitle; }

    void SetTitle(const wxString &title) { m_pTitle = new wxString(title); }

    void AddStudent(Student *student);
    Student &GetStudent(int index) const;
    int StudentCount();

    void AddAssessment(Assessment *assessment);
    Assessment &GetAssessment(int index) const;
    int AssessmentCount();
    void Clear(){m_assessments.clear(); m_students.clear();}

  private:
    wxString *m_pId;
    wxString *m_pTitle;
    vector<Student*> m_students;
    vector<Assessment*> m_assessments;
};

#endif
