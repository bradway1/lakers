#ifndef _GBDIALOGASSIGNMENTSCONTROLLER
#define _GBDIALOGASSIGNMENTSCONTROLLER

#include <wx/dialog.h>
#include <wx/panel.h>
#include <wx/editlbox.h>
#include <wx/combobox.h>
#include <wx/event.h>
#include <wx/statbox.h>

#include "sql/gbsql.h"

class GBDialogAssessmentView;

class GBDialogAssessmentController
{
	public:
	GBDialogAssessmentController();
	GBDialogAssessmentController(GBDialogAssessmentView *view);
	~GBDialogAssessmentController();
	// Events
	void NewCourseSelected(wxCommandEvent& event);

	private:
	void PopulateCourseChoices();
	void PopulateAssessmentListBox(wxString CourseTitle);
	wxString GetCourseComboBoxSelection(wxString CourseTitle);

  GBSql *m_pSql;  
  vector<Course*> m_courses;
	GBDialogAssessmentView *m_pDialogView;
};

#endif
