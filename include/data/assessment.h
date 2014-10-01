#ifndef _ASSESSMENT_H
#define _ASSESSMENT_H

#include <wx\string.h>
#include <wx\datetime.h>

class Assessment {
    public:
        enum Type : int {
            TEST,
            PROJECT,
            HOMEWORK
        };
        
        Assessment();
        ~Assessment();

        void SetId(const wxString &);
        void SetCourseId(const wxString &);
        void SetTitle(const wxString &);
        void SetDate(const wxDateTime &);
        void SetType(Assessment::Type);

        wxString *GetId() const;
        wxString *GetCourseId() const;
        wxString *GetTitle() const;
        wxDateTime *GetDate() const;
        Assessment::Type GetType() const;

    private:
        wxString *m_pId;
        wxString *m_pCid;
        wxString *m_pTitle;
        wxDateTime *m_pDate;
        Assessment::Type m_type;
};

#endif
