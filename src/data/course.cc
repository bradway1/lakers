#include "data/course.h"

Course::Course()
  : m_pId(NULL),
    m_pTitle(NULL),
    m_students(),
    m_assessments() {

}

Course::Course(const wxString &id)
  : m_pId(new wxString(id)),
    m_pTitle(NULL),
    m_students(),
    m_assessments() {

}

Course::~Course() {
  delete m_pId;
  delete m_pTitle;
}

void Course::AddStudent(Student *student) {
  m_students.push_back(student);
}

Student &Course::GetStudent(int index) const {
  return *m_students[index];
}

int Course::StudentCount() {
  return m_students.size();
}

void Course::AddAssessment(Assessment *assessment) {
  m_assessments.push_back(assessment);
}

Assessment &Course::GetAssessment(int index) const {
  return *m_assessments[index];
}

int Course::AssessmentCount() {
  return m_assessments.size();
}
