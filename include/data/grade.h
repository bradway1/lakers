#ifndef _GRADE_H_
#define _GRADE_H_

#include <wx/string.h>

class Grade {
  public:
    Grade();
    Grade(const wxString &id);
    ~Grade();

    wxString &Id() const { return *m_pId; }
    wxString &Value() const { return *m_pValue; }
    wxString &AssessmentId() const { return *m_pAId; }

    void SetValue(const wxString &value) { m_pValue = new wxString(value); }
    void SetAssessmentId(const wxString &aid) { m_pAId = new wxString(aid); }

  private:
    wxString *m_pId;
    wxString *m_pAId;
    wxString *m_pValue;
};

#endif
