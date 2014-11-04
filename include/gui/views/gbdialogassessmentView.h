#ifndef _GBDIALOGASSESSMENT
#define _GBDIALOGASSESSMENT


#include "gui\controllers\gbdialogassessmentController.h"


#define GB_ASSIGNMENT_DIALOGSIZE wxSize(350,450)

class GBDialogAssessmentView
{
	friend class GBDialogAssessmentController;
	public:
	GBDialogAssessmentView();
	GBDialogAssessmentView(wxWindow *parent, wxString CourseTitle);
	~GBDialogAssessmentView()
		{delete m_pCon, m_pDialog, m_pGBDialogPanel, m_pCourseComboBox, m_pModifyAssignmentListBox;}

	void ShowModal(){m_pDialog->ShowModal();}

	protected:
	GBDialogAssessmentController	*m_pCon;
	wxDialog						*m_pDialog;
	wxPanel							*m_pGBDialogPanel;
	wxComboBox 						*m_pCourseComboBox;
	wxEditableListBox				*m_pModifyAssignmentListBox;

};

enum {
	ID_CourseDropDownListAssessment = 1,
};



#endif
