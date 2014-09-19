#include "data/course.h"

Course::Course() {

}

Course::~Course() {

}

void Course::SetId(const wxString &id) {
    m_pId = new wxString(id);
}

void Course::SetTitle(const wxString &title) {
    m_pTitle = new wxString(title);
}

void Course::SetStart(const wxDateTime &start) {
    m_pStart = new wxDateTime(start);
}

void Course::SetEnd(const wxDateTime &end) {
    m_pEnd = new wxDateTime(end);
}

wxString *Course::GetId() const {
    return m_pId;
}

wxString *Course::GetTitle() const {
    return m_pTitle;
}

wxDateTime *Course::GetStart() const {
    return m_pStart;
}

wxDateTime *Course::GetEnd() const {
    return m_pEnd;
}
