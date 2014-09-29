#include <wx/wxprec.h>
#include <wx/notebook.h>
#include <wx/panel.h>
#include <wx/arrstr.h>
#include <wx/choice.h>
#include <wx/textctrl.h>
#include <wx/grid.h>
#include <stdlib.h>
#include <wx/sizer.h>
#include <wx/colour.h>
#include <wx/toolbar.h>
#include <wx/bitmap.h>



#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#define GBAPPSIZE wxSize(800,600)



class GBFrame: public wxFrame
{
public:
    GBFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:

	void PopulateCourseDropDownList();
	void CreateStudentGridView();
    void AddCourse(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    wxChoice	*m_pCourseDropDownList;                     // Create an obj for Dropdown list of type wxChoicebook
    wxPanel		*m_pGBFramePanel;
	wxTextCtrl	*m_pCourseDisplay;                          // Declare a text control box calles course display
	wxGrid		*m_pGridView;
	wxButton	*m_pbtn_AddAssignment;
	wxToolBar	*m_pUserOptionsToolBar;

    wxDECLARE_EVENT_TABLE();
};

enum
{
    ID_AddCourseMenuSelect = 1,
    ID_CourseDropDownList = 2,
    ID_GradeBookPanel = 3,
    ID_GridView = 4,
    ID_btn_AddAssignment = 5
};