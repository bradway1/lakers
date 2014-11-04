#include "gui\views\gbdialogassessmentView.h"
#include "sql\gbsql.h"


GBDialogAssessmentView::GBDialogAssessmentView() { }

GBDialogAssessmentView::GBDialogAssessmentView(wxWindow *parent, wxString CourseTitle)
{
	wxStaticBox				*CourseSelectStaticBox;
	wxStaticBox 			*ModifyAssignmentStaticBox;

	// Create Dialog
	m_pDialog = new wxDialog(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, GB_ASSIGNMENT_DIALOGSIZE, wxDEFAULT_DIALOG_STYLE, "GBDialog");
	m_pDialog->SetTitle("Edit Assignment(s)");
	// Create Panel
	m_pGBDialogPanel = new wxPanel(m_pDialog, wxID_ANY, wxPoint(0,0), GB_ASSIGNMENT_DIALOGSIZE, wxTAB_TRAVERSAL, "ID_GBDialogPanel");
	// Create Static Boxes
	CourseSelectStaticBox = new wxStaticBox(m_pGBDialogPanel, wxID_ANY, "Select Course", wxPoint(10,10), wxSize(325,75), 0,"Select Course");
	ModifyAssignmentStaticBox = new wxStaticBox(m_pGBDialogPanel, wxID_ANY, "Modify Assignment", wxPoint(10,100), wxSize(325, 175), 0,"Select Course");
	// Create ComboBox
	m_pCourseComboBox = new wxComboBox(m_pGBDialogPanel, ID_CourseDropDownListAssessment, CourseTitle, wxPoint(20,40), wxSize(100, 25));
	// Create Assignment EditableListBox
	m_pModifyAssignmentListBox = new wxEditableListBox(m_pGBDialogPanel, wxID_ANY, "Modify Assignment(s)", wxPoint(20,125), wxSize(310,130), wxEL_DEFAULT_STYLE, "Modify Assignment(s)");
	// Connect Controller
	m_pCon = new GBDialogAssessmentController(this, CourseTitle);
	// Connect Event Handler to Controller
	m_pCourseComboBox->Bind(wxEVT_TEXT, &GBDialogAssessmentController::NewCourseSelected, m_pCon);
}
