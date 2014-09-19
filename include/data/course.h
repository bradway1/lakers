#ifndef _COURSE_H
#define _COURSE_H

#include <wx/datetime.h>

class Course {
    public:
        Course();
        ~Course();

        void SetId(const wxString &);
        void SetTitle(const wxString &);
        void SetStart(const wxDateTime &);
        void SetEnd(const wxDateTime &);

        wxString *GetId() const;
        wxString *GetTitle() const;
        wxDateTime *GetStart() const;
        wxDateTime *GetEnd() const;

    private:
        wxString *m_pId;
        wxString *m_pTitle;
        wxDateTime *m_pStart;
        wxDateTime *m_pEnd;
};

#endif
