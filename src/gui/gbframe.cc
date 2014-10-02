#include "gui\gbframe.h"

wxBEGIN_EVENT_TABLE(GBFrame, wxFrame)
    EVT_MENU(wxID_EXIT,                		GBFrame::OnExit)
    EVT_MENU(wxID_ABOUT,               		GBFrame::OnAbout)
    EVT_MENU(ID_AddCourseMenuSelect,   		GBFrame::AddCourse)
    EVT_MENU(ID_btn_ToolBarAddAssignment,	GBFrame::AddAssignment)
    EVT_MENU(ID_btn_ToolBarEditAssignment,	GBFrame::EditAssignment)
wxEND_EVENT_TABLE()


GBFrame::GBFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(NULL, wxID_ANY, title, pos, size)
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
	m_pUserOptionsToolBar->AddTool(ID_btn_ToolBarAddAssignment, "Add Assignment", wxBitmap(wxImage(_T("C:\\lakers\\resources\\AddAssignment.bmp"))), "Add Assignemt(s)", wxITEM_NORMAL );
	m_pUserOptionsToolBar->AddTool(ID_btn_ToolBarEditAssignment, "Edit Assignment", wxBitmap(wxImage(_T("C:\\lakers\\resources\\EditAssignment.bmp"))), "Edit Assignemt(s)", wxITEM_NORMAL );
	m_pUserOptionsToolBar->Realize();

	// Create Frame Sizers
	m_pCourseDropDownListSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pGBFrameSizer = new wxBoxSizer(wxVERTICAL);

	// Create Base Panel
    m_pGBFramePanel = new wxPanel(this, ID_GradeBookPanel, wxPoint(0,0), GBAPPSIZE, wxTAB_TRAVERSAL, "GBFramePanel");
	m_pGBFramePanel->SetBackgroundColour(wxColour(char(255),char(255), char(255), char(0) ));//wxWHITE

	// Add CourseDropDownList and GridView to Panel
	m_pCourseDropDownList = new wxChoice(m_pGBFramePanel, ID_CourseDropDownList, wxDefaultPosition, wxSize(100, 25), 0, 0, 0, wxDefaultValidator, _T("CourseDropDownList"));
	m_pGridView = new wxGrid(m_pGBFramePanel, ID_GridView, wxDefaultPosition, GBAPPSIZE, 0, "ID_GridView" );

	// Apply Sizer to CourseDropDownList and GridView
	m_pCourseDropDownListSizer->Add(m_pCourseDropDownList, 0, wxLEFT | wxTOP, 25);
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


}

void GBFrame::EditAssignment(wxCommandEvent& event)
{
	// Handle Event

}

void GBFrame::AddAssignment(wxCommandEvent& event)
{
	// Handle Event

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
void GBFrame::AddCourse(wxCommandEvent& event)
{
    wxLogMessage("Dialog Box Screen ... needs development ");
}