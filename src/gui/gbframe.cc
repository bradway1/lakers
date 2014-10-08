#include "gui\gbframe.h"

#include "sql\gbsql.h"

wxBEGIN_EVENT_TABLE(GBFrame, wxFrame)
    EVT_MENU(wxID_EXIT,                			GBFrame::OnExit)
    EVT_MENU(wxID_ABOUT,               			GBFrame::OnAbout)
    EVT_MENU(ID_AddCourseMenuSelect,   			GBFrame::AddCourse)
    EVT_MENU(ID_ModifyAssignmentToolBarButton,	GBFrame::ModifyAssignments)
wxEND_EVENT_TABLE()


GBFrame::GBFrame(const wxString& title, const wxPoint& pos, const wxSize& size): wxFrame(NULL, wxID_ANY, title, pos, size)
{

	// Create File Menu
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_AddCourseMenuSelect, "&Add Course...\tCtrl-G", "Add a course to your GradeBook");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, "&File" );
    menuBar->Append( menuHelp, "&Help" );
    SetMenuBar( menuBar );
    CreateStatusBar();
    SetStatusText( "Welcome to GradeBook!" );

	// Create ToolBar
	m_pUserOptionsToolBar = this->CreateToolBar(wxTB_DEFAULT_STYLE, wxID_ANY, "ID_ToolBar");
	m_pUserOptionsToolBar->SetBackgroundColour(wxColour(char(255),char(255), char(255), char(0) ));
	m_pModifyAssignmentToolBarButton = new wxToolBarToolBase(NULL, ID_ModifyAssignmentToolBarButton, "Modify Assignment", wxBitmap(wxImage(_T("\\lakers\\resources\\Assignment.bmp"))),  wxNullBitmap, wxITEM_NORMAL, NULL, "Modify Assignment(s)", wxEmptyString);
	m_pUserOptionsToolBar->AddTool(m_pModifyAssignmentToolBarButton);
	m_pUserOptionsToolBar->Realize();

	// Create Frame Sizers
	m_pCourseDropDownListSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pGBFrameSizer = new wxBoxSizer(wxVERTICAL);

	// Create Base Panel
    m_pGBFramePanel = new wxPanel(this, ID_GradeBookPanel, wxPoint(0,0), GBAPPSIZE, wxTAB_TRAVERSAL, "GBFramePanel");
	m_pGBFramePanel->SetBackgroundColour(wxColour(char(255),char(255), char(255), char(0) ));//wxWHITE

	// Add CourseDropDownList and GridView to Panel
	m_pCourseComboBox = new wxComboBox(m_pGBFramePanel, ID_CourseDropDownList, \
      wxEmptyString, wxDefaultPosition, wxSize(200, 20));
	m_pCourseComboBox->SetEditable(false);
  
  m_pGridView = new wxGrid(m_pGBFramePanel, ID_GridView, wxDefaultPosition, GBAPPSIZE, 0, "ID_GridView" );

	// Apply Sizer to CourseDropDownList and GridView
	m_pCourseDropDownListSizer->Add(m_pCourseComboBox, 0, wxLEFT | wxTOP, 25);
	m_pGBFrameSizer->Add(m_pCourseDropDownListSizer, 0 , 0);
	m_pGBFrameSizer->Add(m_pGridView, 0, wxEXPAND | wxALL, 25);

	// Set GBFrameSizer as primary sizer
	m_pGBFramePanel->SetSizer(m_pGBFrameSizer);

	PopulateCourseDropDownList();
	CreateGridView();

}

// *** Modify grid to populate it with data pulled from DB ***
void GBFrame::CreateGridView()
{
	// Create Student Grid view.
	// Number of students in course = rows
	// Total assessments = columns
	m_pGridView->CreateGrid( 30, 10 );
	m_pGridView->SetBackgroundColour(wxColour(char(255),char(255), char(255), char(0)));
	m_pGridView->Refresh();

	m_pGridView->EnableDragColMove(true);
    m_pGridView->EnableEditing(true);

	// Pull Data from DB
}

// *** Need to pull data from DB to populate Dropdown list ***
void GBFrame::PopulateCourseDropDownList()
{
    GBSql sql;
    vector<Course*> courseVec;

    if (sql.SelectCourse(&courseVec) < 0) { 
      return; 
    }

    for (int i = 0; i < courseVec.size(); ++i) {
      Course *pCourse = courseVec[i];
    
      m_pCourseComboBox->Append(*pCourse->GetTitle());
    }

    if (m_pCourseComboBox->GetCount() > 0) {
      m_pCourseComboBox->SetSelection(0);
    }
}

void GBFrame::AssignmentSelected(wxCommandEvent& event)
{
	// Handle Event when assignment is selected inside
	// the "Edit Assignment" dialog box.
}


void GBFrame::ModifyAssignments(wxCommandEvent& event)
{
	// Handle Event
	wxChoice				*ChooseCourseDropDownList;
	wxArrayString			 Assignments;
	wxStaticBox				*CourseSelectStaticBox;
	wxStaticBox 			*ModifyAssignmentStaticBox;
	wxEditableListBox		*ModifyAssignmentListBox;
	wxStaticText			*RenameAssignmentStaticText;

	// Create Dialog
	m_pGBDialog = new wxDialog(this, ID_GBDialog, "Edit Assignment", wxDefaultPosition, GBDIALOGSIZE, wxDEFAULT_DIALOG_STYLE, "ID_GBDialog");
	// Create Panel
    m_pGBDialogPanel = new wxPanel(m_pGBDialog, ID_GBDialogPanel, wxPoint(0,0), GBDIALOGSIZE, wxTAB_TRAVERSAL, "ID_GBDialogPanel");
	// Create Static Boxes
	CourseSelectStaticBox = new wxStaticBox(m_pGBDialogPanel, wxID_ANY, "Select Course", wxPoint(10,10), wxSize(325,75), 0,"Select Course");
	ModifyAssignmentStaticBox = new wxStaticBox(m_pGBDialogPanel, wxID_ANY, "Modify Assignment", wxPoint(10,100), wxSize(325, 175), 0,"Select Course");
	// Create DropdownList
	ChooseCourseDropDownList = new wxChoice(m_pGBDialogPanel, wxID_ANY, wxPoint(20,40), wxSize(100, 25), 0, 0, 0, wxDefaultValidator, _T("ChooseCourse"));
	// Create Assignment EditableListBox
	ModifyAssignmentListBox = new wxEditableListBox(m_pGBDialogPanel, wxID_ANY, "Modify Assignment(s)", wxPoint(20,125), wxSize(310,130), wxEL_DEFAULT_STYLE, "Modify Assignment(s)");
	Assignments.Alloc(10); /* Modify to allocate enough memory for the correct total assignemtns in DB */
	ModifyAssignmentListBox->SetStrings(Assignments);
	// Connect GBFrame::AssignmentSelected to handle event from EditableListBox
	ModifyAssignmentListBox->Bind(wxEVT_LIST_ITEM_SELECTED, &GBFrame::AssignmentSelected, this);
	// Show Dialog
	m_pGBDialog->ShowModal();
}


void GBFrame::AddCourse(wxCommandEvent& event)
{
	wxGrid					*AddCourseGridView;
	wxStaticBox				*CourseNameStaticBox;
	wxStaticBox				*CourseNumberStaticBox;
	wxStaticBox				*ImportStudentCSVStaticBox;
	wxTextCtrl				*CourseNameTextCtrl;
	wxTextCtrl				*CourseNumberTextCtrl;
	wxFilePickerCtrl		*ImportStudentCSVFilePickerCtrl;

	// Create Dialog
	m_pGBDialog = new wxDialog(this, ID_GBDialog, "Add Course", wxDefaultPosition, GBDIALOGSIZE, wxDEFAULT_DIALOG_STYLE, "ID_GBDialog");
	// Create Panel
    m_pGBDialogPanel = new wxPanel(m_pGBDialog, ID_GBDialogPanel, wxPoint(0,0), GBDIALOGSIZE, wxTAB_TRAVERSAL, "ID_GBDialogPanel");
	// Create Static Box and TextCtrl
	CourseNameStaticBox = new wxStaticBox(m_pGBDialogPanel, wxID_ANY, "Course Name", wxPoint(10,10), wxSize(325,50), 0,"Course Name");
	CourseNameTextCtrl	= new wxTextCtrl(m_pGBDialogPanel, wxID_ANY, wxEmptyString, wxPoint(20,30), wxSize(300,25), wxTE_CAPITALIZE, wxDefaultValidator, "CourseNameTextCtrl");
	CourseNumberStaticBox =  new wxStaticBox(m_pGBDialogPanel, wxID_ANY, "Course Number", wxPoint(10,75), wxSize(325,50), 0,"Course Number");
	CourseNumberTextCtrl  = new wxTextCtrl(m_pGBDialogPanel, wxID_ANY, wxEmptyString, wxPoint(20,95), wxSize(300,25), wxTE_CAPITALIZE, wxDefaultValidator, "CourseNumberTextCtrl");
	ImportStudentCSVStaticBox =  new wxStaticBox(m_pGBDialogPanel, wxID_ANY, "Import Students (File: *.csv)", wxPoint(10,140), wxSize(325,50), 0,"Import Students");
	ImportStudentCSVFilePickerCtrl = new wxFilePickerCtrl(m_pGBDialogPanel, wxID_ANY, wxEmptyString, "Select .csv file", "*.csv", wxPoint(20,160),  wxDefaultSize, wxFLP_DEFAULT_STYLE, wxDefaultValidator, "ImportStudentCSVFilePickerCtrl");
	// Show Dialog
	m_pGBDialog->ShowModal();
}

void GBFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}

void GBFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox( "Grade Book Application version 1.0.0",
                  "About", wxOK | wxICON_INFORMATION );
}
