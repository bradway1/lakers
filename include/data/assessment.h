#ifndef _ASSESSMENT_H
#define _ASSESSMENT_H

#include <wx/string.h>

class Assessment {
  public:
    Assessment();
    Assessment(const wxString &id);
    ~Assessment();

    wxString Id() const { return m_id; }
    wxString Title() const { return m_title; }

    void SetTitle(const wxString &title) { m_title = title; }

  private:
    wxString m_id;
    wxString m_title;
};

#endif
