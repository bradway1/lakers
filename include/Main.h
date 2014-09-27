// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#include <wx/choicebk.h>
#include <wx/notebook.h>
#include <wx/panel.h>
#include <wx/textctrl.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#define gbAppSize wxSize(550,250)



class BaseFrame: public wxFrame
{
public:
    BaseFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
    void AddCourse(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    wxChoicebook *DropDown;                     // Create an obj for Dropdown list of type wxChoicebook
	wxTextCtrl* CourseDisplay;                  // Declare a text control box calles course display
	
	
    
    wxDECLARE_EVENT_TABLE();
};

enum
{
    ID_AddCourseMenuSelect = 1,
    ID_ChoiceBook = 2,
    ID_GradeBookPanel = 3,
	ID_CourseDisplay = 4
};