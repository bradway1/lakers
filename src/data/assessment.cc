#include "data\assessment.h"

Assessment::Assessment() 
  : m_pId(NULL),
    m_pTitle(NULL) {

}

Assessment::Assessment(const wxString &id)
  : m_pId(new wxString(id)),
    m_pTitle(NULL) {

}

Assessment::~Assessment() {
  delete m_pId;
  delete m_pTitle;
}
