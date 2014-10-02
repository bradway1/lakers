#include <stdlib.h>
#include <wx/wxprec.h>
#include <wx/notebook.h>
#include <wx/panel.h>
#include <wx/arrstr.h>
#include <wx/choice.h>
#include <wx/textctrl.h>
#include <wx/grid.h>
#include <wx/sizer.h>
#include <wx/colour.h>
#include <wx/toolbar.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/dialog.h>



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
	void CreateGridView();
    void AddCourse(wxCommandEvent& event);
    void EditAssignment(wxCommandEvent& event);
    void AddAssignment(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

	wxBoxSizer 	*m_pCourseDropDownListSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer 	*m_pGBFrameSizer = new wxBoxSizer(wxVERTICAL);
    wxChoice	*m_pCourseDropDownList;
    wxPanel		*m_pGBFramePanel;
	wxTextCtrl	*m_pCourseDisplay;
	wxGrid		*m_pGridView;
	wxButton	*m_pbtn_AddAssignment;
	wxToolBar	*m_pUserOptionsToolBar;
	wxDialog	*m_pAssessmentFrame;

    wxDECLARE_EVENT_TABLE();
};

enum
{
    ID_AddCourseMenuSelect = 1,
    ID_CourseDropDownList = 2,
    ID_GradeBookPanel = 3,
    ID_GridView = 4,
    ID_btn_AddAssignment = 5,
    ID_btn_ToolBarAddAssignment = 6,
    ID_btn_ToolBarEditAssignment = 7,
    ID_AssessmentFrame = 8,
};