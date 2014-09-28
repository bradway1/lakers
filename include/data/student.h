#ifndef _STUDENT_H
#define _STUDENT_H

#include <wx\string.h>

class Student {
    public:
        Student();
        ~Student();
        
        void SetStudentId(const wxString &);
        void SetFirst(const wxString &);
        void SetLast(const wxString &);

        wxString *GetStudentId() const;
        wxString *GetFirst() const;
        wxString *GetLast() const;

    private:
        wxString *m_pStudentId;
        wxString *m_pFirst;
        wxString *m_pLast;
};

#endif
