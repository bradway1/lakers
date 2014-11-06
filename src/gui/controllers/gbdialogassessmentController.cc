#include "gui\controllers\gbdialogassessmentController.h"
#include "sql\gbsql.h"
#include "gui\views\gbdialogassessmentView.h"

// Constructor 1
GBDialogAssessmentController::GBDialogAssessmentController(){}

// Constructor 2
GBDialogAssessmentController::GBDialogAssessmentController(GBDialogAssessmentView *view)
  : m_pDialogView(view),
    m_pSql(GBSql::Instance()) {
	PopulateCourseChoices();
  PopulateAssessmentListBox(m_pDialogView->m_pCourseComboBox->GetStringSelection());
}

GBDialogAssessmentController::~GBDialogAssessmentController() {

}

// NewCourseSelected()
void GBDialogAssessmentController::NewCourseSelected(wxCommandEvent& event){
	PopulateAssessmentListBox((m_pDialogView->m_pCourseComboBox)->GetStringSelection());
}

// PopulateAssessmentListBox()
void GBDialogAssessmentController::PopulateAssessmentListBox(wxString CourseTitle){
  Course *course(NULL);
  
  if (CourseTitle.IsEmpty() && m_courses.size() > 0) {
    CourseTitle = m_courses[0]->Title();
  }

  for (int i = 0; i < m_courses.size(); ++i) {
    if (m_courses[i]->Title().IsSameAs(CourseTitle)) {
      course = m_courses[i];

      break;
    }
  }

  if (course == NULL) {
    return;
  }

  if (m_pSql->SelectAssessmentsByCourse(*course) == -1) {
    return;
  }

  wxArrayString values;

  for (int i = 0; i < course->AssessmentCount(); ++i) {
    values.Add(course->GetAssessment(i).Title());
  } 

  m_pDialogView->m_pModifyAssignmentListBox->SetStrings(values); 
}

// GetCourseComboBoxSelection()
wxString GBDialogAssessmentController::GetCourseComboBoxSelection(wxString CourseTitle){
	return "-1";
}


// PopulateCourseChoices()
void GBDialogAssessmentController::PopulateCourseChoices(){
  wxComboBox *combo = m_pDialogView->m_pCourseComboBox; 
  
  if (m_pSql->SelectCourses(&m_courses) == -1) {
    return;
  }

  for (int i = 0; i < m_courses.size(); ++i) {
    combo->Append(m_courses[i]->Title()); 
  }

  if (combo->GetCount() > 0) {
    combo->SetValue(m_courses[0]->Title());
  }
}
