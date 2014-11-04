#include "data\grade.h"

Grade::Grade()
  : m_pId(NULL),
    m_pAId(NULL),
    m_pValue(NULL) {

}

Grade::Grade(const wxString &id)
  : m_pId(new wxString(id)),
    m_pAId(NULL),
    m_pValue(NULL) {

}

Grade::~Grade() {
  delete m_pId;
  delete m_pAId;
  delete m_pValue;
}
