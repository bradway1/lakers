#include "data\student.h"

Student::Student() {

}

Student::Student(const wxString &id)
  : m_pId(new wxString(id)),
    m_pFirst(NULL),
    m_pLast(NULL),
    m_grades() {

}

Student::~Student() {
  delete m_pId;
  delete m_pFirst;
  delete m_pLast;
}

void Student::AddGrade(Grade *Grade) {
  m_grades.push_back(Grade);
}

Grade &Student::GetGrade(int index) const {
  return *m_grades[index];
}

int Student::GradeCount() {
  return m_grades.size();
}
