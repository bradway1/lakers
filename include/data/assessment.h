#ifndef _ASSESSMENT_H
#define _ASSESSMENT_H

#include <wx/string.h>

class Assessment {
  public:
    Assessment();
    Assessment(const wxString &id);
    ~Assessment();

    wxString &Id() const { return *m_pId; }
    wxString &Title() const { return *m_pTitle; }

    void SetTitle(const wxString &title) { m_pTitle = new wxString(title); }

  private:
    wxString *m_pId;
    wxString *m_pTitle;
};

#endif
