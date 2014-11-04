#ifndef _GBDIALOGASSIGNMENTSCONTROLLER
#define _GBDIALOGASSIGNMENTSCONTROLLER

#include <wx/dialog.h>
#include <wx/panel.h>
#include <wx/editlbox.h>
#include <wx/combobox.h>
#include <wx/event.h>
#include <wx/statbox.h>


class GBDialogAssessmentView;

class GBDialogAssessmentController
{
	public:
	GBDialogAssessmentController();
	GBDialogAssessmentController(GBDialogAssessmentView *view, wxString CourseTitle);
	~GBDialogAssessmentController();
	// Events
	void NewCourseSelected(wxCommandEvent& event);

	private:
	void PopulateCourseChoices();
	void PopulateAssignmentListBox(wxString CourseTitle);
	wxString GetCourseComboBoxSelection(wxString CourseTitle);
	GBDialogAssessmentView *m_pDialogView;


};

#endif
