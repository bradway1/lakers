#include "data\assessment.h"

Assessment::Assessment() {

}

Assessment::~Assessment() {
    delete m_pId;

    delete m_pCid;

    delete m_pTitle;

    delete m_pDate;
}

void Assessment::SetId(const wxString &id) {
    m_pId = new wxString(id);
}

void Assessment::SetCourseId(const wxString &cid) {
    m_pCid = new wxString(cid);
}

void Assessment::SetTitle(const wxString &title) {
    m_pTitle = new wxString(title);
}

void Assessment::SetDate(const wxDateTime &date) {
    m_pDate = new wxDateTime(date);
}

void Assessment::SetType(Assessment::Type type) {
    m_type = type;
}

wxString *Assessment::GetId() const {
    return m_pId;
}

wxString *Assessment::GetCourseId() const {
    return m_pCid;
}

wxString *Assessment::GetTitle() const {
    return m_pTitle;
}

wxDateTime *Assessment::GetDate() const {
    return m_pDate;
}

Assessment::Type Assessment::GetType() const {
    return m_type;
}
