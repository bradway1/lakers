#include "gui\controllers\gbframeController.h"
#include "sql\gbsql.h"
#include "gui\views\gbframeView.h"

#include <iostream>

using namespace std;

GBFrameController::GBFrameController(GBFrameView *view)
  : m_pMainFrameView(view),
    m_pSql(GBSql::Instance()) {

  m_pSql->AddSubscriber(this);

	PopulateCourseDropDownList();
  
	CreateGridView();
}

GBFrameController::~GBFrameController() {
  delete m_pMainFrameView;
  delete m_pDialogAssessmentView;
  delete m_pDialogCourse;

  m_pSql->RemoveSubscriber(this);

  for (int i = 0; i < m_courses.size(); ++i) {
    delete m_courses[i];
  }
}

// *** Modify grid to populate it with data pulled from DB ***
void GBFrameController::CreateGridView(){
	// Create Student Grid view.
	// Number of students in course = rows
	// Total assessments = columns
  (m_pMainFrameView->m_pGridView)->CreateGrid(0, 0);
  (m_pMainFrameView->m_pGridView)->SetBackgroundColour(wxColour(char(255),char(255), char(255), char(0)));
	(m_pMainFrameView->m_pGridView)->EnableDragColMove(true);
	(m_pMainFrameView->m_pGridView)->EnableEditing(true);

  UpdateGridView();
}

void GBFrameController::UpdateGridView() {
  Course *course(NULL);
  wxGrid *grid = m_pMainFrameView->m_pGridView;
  wxComboBox *combo = m_pMainFrameView->m_pCourseComboBox;
  wxString strSelection = combo->GetStringSelection();

  if (strSelection.IsEmpty() && m_courses.size() > 0) {
    strSelection = m_courses[0]->Title();
  }

  for (int i = 0; i < m_courses.size(); ++i) {
    if (m_courses[i]->Title().IsSameAs(strSelection)) {
      course = m_courses[i];

      break;
    }
  }

  if (course == NULL) {
    cerr << "Failed to find selected course" << endl;

    return;
  }

  if (m_pSql->SelectStudentsByCourse(*course) == -1) {
    cerr << "Failed to select students in course" << endl;

    return;
  }

  if (course->StudentCount() > grid->GetNumberRows()) {
    grid->AppendRows(course->StudentCount() - grid->GetNumberRows());
  } else if (course->StudentCount() < grid->GetNumberRows()) {
    grid->DeleteRows(0, grid->GetNumberRows() - course->StudentCount());
  }

  for (int i = 0; i < course->StudentCount(); ++i) {
    grid->SetRowLabelValue(i, wxString::Format("%s, %s", course->GetStudent(i).Last(), course->GetStudent(i).First()));
  }

  if (m_pSql->SelectAssessmentsByCourse(*course) == -1) {
    cerr << "Failed to select assessments in course" << endl;

    return;
  }

  if (course->AssessmentCount() > grid->GetNumberCols()) {
    grid->AppendCols(course->AssessmentCount() - grid->GetNumberCols());
  } else if (course->AssessmentCount() < grid->GetNumberCols()) {
    grid->DeleteCols(0, grid->GetNumberCols() - course->AssessmentCount());
  }

  for (int i = 0; i < course->AssessmentCount(); ++i) {
    grid->SetColLabelValue(i, course->GetAssessment(i).Title());
  }

  grid->Refresh();
}

void  GBFrameController::NewCourseSelected(wxCommandEvent& event){
  UpdateGridView();
}

void GBFrameController::OnCourseUpdate() {
  PopulateCourseDropDownList();
}

// *** Need to pull data from DB to populate Dropdown list ***
void GBFrameController::PopulateCourseDropDownList(){
  wxComboBox *course = m_pMainFrameView->m_pCourseComboBox;

  m_courses.clear();

  if (m_pSql->SelectCourses(&m_courses) == -1) {
    return;
  }

  course->Clear();  

  for (int i = 0; i < m_courses.size(); ++i) {
    course->Append(m_courses[i]->Title());
  }

  if (course->GetCount() > 0) {
    course->SetValue(m_courses[0]->Title());
  }
}


void GBFrameController::ModifyAssignments(wxCommandEvent& event){
	// Handle Event
	m_pDialogAssessmentView = new GBDialogAssessmentView(m_pMainFrameView);
	m_pDialogAssessmentView->ShowModal();
}


void GBFrameController::AddCourse(wxCommandEvent& event){
	// Handle Event
	m_pDialogCourse = new GBDialogCourseView(m_pMainFrameView);
	m_pDialogCourse->ShowModal();
}

void GBFrameController::OnExit(wxCommandEvent& event) {
	// Handle Event
    (m_pMainFrameView->Close)( true );
}

void GBFrameController::OnAbout(wxCommandEvent& event) {
	// Handle Event
    wxMessageBox( "Grade Book Application version 1.0.0",
                  "About", wxOK | wxICON_INFORMATION );
}

