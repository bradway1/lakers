#include <stdlib.h>
#include <wx/wxprec.h>
#include <wx/panel.h>
#include <wx/grid.h>
#include <wx/editlbox.h>
#include <wx/listctrl.h>
#include <wx/event.h>
#include <wx/filepicker.h>
#include <wx/combobox.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#define GBAPPSIZE wxSize(800,600)
#define GBDIALOGSIZE wxSize(350,450)



class GBFrame: public wxFrame
{
public:
    GBFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

private:

	void PopulateCourseDropDownList();
	void CreateGridView();
	// Events
    void AddCourse(wxCommandEvent& event);
    void ModifyAssignments(wxCommandEvent& event);
    void AssignmentSelected(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

	wxBoxSizer 			*m_pCourseDropDownListSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer 			*m_pGBFrameSizer = new wxBoxSizer(wxVERTICAL);
  wxComboBox *m_pCourseComboBox;  
  wxChoice			*m_pCourseDropDownList;
    wxPanel				*m_pGBFramePanel;
	wxGrid				*m_pGridView;
	wxToolBar			*m_pUserOptionsToolBar;
	wxToolBarToolBase	*m_pModifyAssignmentToolBarButton;
	wxDialog			*m_pGBDialog;
	wxPanel				*m_pGBDialogPanel;
	wxEditableListBox 	*SelectAssignmentListBox;
	wxFilePickerCtrl 	*m_pSelectFileLocation;

    wxDECLARE_EVENT_TABLE();
};


enum
{
	ID_AddCourseMenuSelect = 1,
	ID_CourseDropDownList = 2,
	ID_GradeBookPanel = 3,
	ID_GridView = 4,
	ID_AddAssignmentToolBarButton = 5,
	ID_ModifyAssignmentToolBarButton = 6,
	ID_GBDialogPanel = 7,
	ID_GBDialog = 8,
	ID_SelectAssignmentListBox = 9
};
