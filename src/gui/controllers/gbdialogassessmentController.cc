#include "gui\controllers\gbdialogassessmentController.h"
#include "sql\gbsql.h"
#include "gui\views\gbdialogassessmentView.h"

// Constructor 1
GBDialogAssessmentController::GBDialogAssessmentController(){}
// Constructor 2
GBDialogAssessmentController::GBDialogAssessmentController(GBDialogAssessmentView *view, wxString CourseTitle): m_pDialogView(view)
{
	PopulateCourseChoices();
	PopulateAssignmentListBox(CourseTitle);
}

// NewCourseSelected()
void GBDialogAssessmentController::NewCourseSelected(wxCommandEvent& event){

	PopulateAssignmentListBox((m_pDialogView->m_pCourseComboBox)->GetStringSelection());
}

// PopulateAssignmentListBox()
void GBDialogAssessmentController::PopulateAssignmentListBox(wxString CourseTitle){

	wxArrayString assignments;
	GBSql sql;
	vector<Assessment*> AssessmentVec;
	sql.SelectAssesmentFromCourse(&AssessmentVec, GetCourseComboBoxSelection(CourseTitle));
	Assessment *pAssessment;

	assignments.Alloc(AssessmentVec.size());

	for(int i = 0; i < AssessmentVec.size(); i++){
		pAssessment = AssessmentVec[i];
		assignments.Add(*pAssessment->GetTitle(),1);
	}
	(m_pDialogView->m_pModifyAssignmentListBox)->SetStrings(assignments);
}

// GetCourseComboBoxSelection()
wxString GBDialogAssessmentController::GetCourseComboBoxSelection(wxString CourseTitle){

	GBSql sql;
	vector<Course*> CourseVec;
	sql.SelectCourse(&CourseVec);
	Course *pCourse;

	for(int i = 0; i < CourseVec.size(); i++){
		pCourse = CourseVec[i];
		if( CourseTitle.IsSameAs(*pCourse->GetTitle(), true) )
			return *pCourse->GetId();
	}

	return "-1";

}


// PopulateCourseChoices()
void GBDialogAssessmentController::PopulateCourseChoices(){

	GBSql sql;
	vector<Course*> courseVec;
	sql.SelectCourse(&courseVec);
	Course *pCourse;

	for (int i = 0; i < courseVec.size(); ++i) {
	  pCourse = courseVec[i];
	  (m_pDialogView->m_pCourseComboBox)->Append(*pCourse->GetTitle());
	}

}
