#include <wx/wxprec.h>
#include <wx/notebook.h>
#include <wx/panel.h>
#include <wx/arrstr.h>
#include <wx/choice.h>
#include <wx/textctrl.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#define GBAPPSIZE wxSize(800,600)



class BaseFrame: public wxFrame
{
public:
    BaseFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:

	void PopulateCourseDropDownList();
    void AddCourse(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    wxChoice *CourseDropDownList;                     // Create an obj for Dropdown list of type wxChoicebook
    wxPanel *BaseFramePanel;
	wxTextCtrl* CourseDisplay;                  // Declare a text control box calles course display

    wxDECLARE_EVENT_TABLE();
};

enum
{
    ID_AddCourseMenuSelect = 1,
    ID_CourseDropDownList = 2,
    ID_GradeBookPanel = 3,
    ID_CourseDisplay = 4
};