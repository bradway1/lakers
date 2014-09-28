#include "data\student.h"

Student::Student()
    :   m_pStudentId(NULL),
        m_pFirst(NULL),
        m_pLast(NULL) {

}

Student::~Student() {
    delete m_pStudentId;

    delete m_pFirst;

    delete m_pLast;
}

void Student::SetStudentId(const wxString &id) {
    m_pStudentId = new wxString(id);
}

void Student::SetFirst(const wxString &first) {
    m_pFirst = new wxString(first);
}

void Student::SetLast(const wxString &last) {
    m_pLast = new wxString(last);
}

wxString *Student::GetStudentId() const {
    return m_pStudentId;
}

wxString *Student::GetFirst() const {
    return m_pFirst;
}

wxString *Student::GetLast() const {
    return m_pLast;
}
