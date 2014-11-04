#include "gui\controllers\gbframeController.h"
#include "sql\gbsql.h"
#include "gui\views\gbframeView.h"

GBFrameController::GBFrameController(GBFrameView *view): m_pMainFrameView(view){

	PopulateCourseDropDownList();
	CreateGridView();
}


// *** Modify grid to populate it with data pulled from DB ***
void GBFrameController::CreateGridView(){

	// Pull Data from DB
  	GBSql sql;
    vector<Student*> StudentVec;
    vector<Assessment*> AssessmentVec;
	Student *pStudent;
	Assessment *pAssessment;

	sql.SelectStudentsFromCourse(&StudentVec, GetCourseComboBoxSelection());
	sql.SelectAssesmentFromCourse(&AssessmentVec, GetCourseComboBoxSelection());

	// Create Student Grid view.
	// Number of students in course = rows
	// Total assessments = columns
	(m_pMainFrameView->m_pGridView)->CreateGrid( StudentVec.size(), AssessmentVec.size());
	(m_pMainFrameView->m_pGridView)->SetBackgroundColour(wxColour(char(255),char(255), char(255), char(0)));
	(m_pMainFrameView->m_pGridView)->EnableDragColMove(true);
	(m_pMainFrameView->m_pGridView)->EnableEditing(true);


	for(int i = 0; i < StudentVec.size(); ++i){
		pStudent = StudentVec[i];
		(m_pMainFrameView->m_pGridView)->SetRowLabelValue(i,*pStudent->GetFirst());
	}

	for(int i = 0; i < AssessmentVec.size(); i++){
		pAssessment = AssessmentVec[i];
		(m_pMainFrameView->m_pGridView)->SetColLabelValue(i, *pAssessment->GetTitle());
	}

	(m_pMainFrameView->m_pGridView)->Refresh();
}

wxString GBFrameController::GetCourseComboBoxSelection(){

	GBSql sql;
	vector<Course*> CourseVec;

	sql.SelectCourse(&CourseVec);
	Course *pCourse;

	for(int i = 0; i < CourseVec.size(); i++){
		pCourse = CourseVec[i];

		if((m_pMainFrameView->m_pCourseComboBox)->GetStringSelection().IsSameAs(*pCourse->GetTitle(), true))
			return *pCourse->GetId();
	}

	return "-1";
}


void  GBFrameController::NewCourseSelected(wxCommandEvent& event){

	GBSql sql;
    vector<Student*> StudentVec;
    vector<Assessment*> AssessmentVec;

	sql.SelectAssesmentFromCourse(&AssessmentVec, GetCourseComboBoxSelection());
	sql.SelectStudentsFromCourse(&StudentVec, GetCourseComboBoxSelection());

	Student *pStudent;
	Assessment *pAssessment;

	// Modify Students (rows)
	if(StudentVec.size() > (m_pMainFrameView->m_pGridView)->GetNumberRows()){

		(m_pMainFrameView->m_pGridView)->AppendRows(StudentVec.size() - (m_pMainFrameView->m_pGridView)->GetNumberRows(), true);
	}
	else{

		(m_pMainFrameView->m_pGridView)->DeleteRows(0, (m_pMainFrameView->m_pGridView)->GetNumberRows() - StudentVec.size(), true);
	}

	for(int i = 0; i < StudentVec.size(); ++i){

		pStudent = StudentVec[i];
		(m_pMainFrameView->m_pGridView)->SetRowLabelValue(i,*pStudent->GetFirst());
	}

	// Modify Assesments (cols)
	if(AssessmentVec.size() > (m_pMainFrameView->m_pGridView)->GetNumberCols()){

		(m_pMainFrameView->m_pGridView)->AppendCols(AssessmentVec.size()- (m_pMainFrameView->m_pGridView)->GetNumberCols(), true);
	}
	else{

		(m_pMainFrameView->m_pGridView)->DeleteCols(0, (m_pMainFrameView->m_pGridView)->GetNumberCols() - AssessmentVec.size(), true);
	}

	for(int i = 0; i < AssessmentVec.size(); i++){
		pAssessment = AssessmentVec[i];
		(m_pMainFrameView->m_pGridView)->SetColLabelValue(i, *pAssessment->GetTitle());
	}

	(m_pMainFrameView->m_pGridView)->Refresh();
}

// *** Need to pull data from DB to populate Dropdown list ***
void GBFrameController::PopulateCourseDropDownList(){

    GBSql sql;
    vector<Course*> courseVec;

    if (sql.SelectCourse(&courseVec) < 0) {
      return;
    }

    for (int i = 0; i < courseVec.size(); ++i) {
      Course *pCourse = courseVec[i];

      (m_pMainFrameView->m_pCourseComboBox)->Append(*pCourse->GetTitle());
    }

    if ((m_pMainFrameView->m_pCourseComboBox)->GetCount() > 0) {
      (m_pMainFrameView->m_pCourseComboBox)->SetSelection(0);
    }
}


void GBFrameController::ModifyAssignments(wxCommandEvent& event){

	// Handle Event
	m_pDialogAssessmentView = new GBDialogAssessmentView(m_pMainFrameView, (m_pMainFrameView->m_pCourseComboBox)->GetStringSelection());
	m_pDialogAssessmentView->ShowModal();
}


void GBFrameController::AddCourse(wxCommandEvent& event){

	// Handle Event
	m_pDialogCourse = new GBDialogCourseView(m_pMainFrameView);
	m_pDialogCourse->ShowModal();
}

void GBFrameController::OnExit(wxCommandEvent& event)
{
	// Handle Event
    (m_pMainFrameView->Close)( true );
}

void GBFrameController::OnAbout(wxCommandEvent& event)
{
	// Handle Event
    wxMessageBox( "Grade Book Application version 1.0.0",
                  "About", wxOK | wxICON_INFORMATION );
}

