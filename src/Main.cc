#include "Main.h"

wxBEGIN_EVENT_TABLE(BaseFrame, wxFrame)
    EVT_MENU(ID_AddCourseMenuSelect,   BaseFrame::AddCourse)
    EVT_MENU(wxID_EXIT,                BaseFrame::OnExit)
    EVT_MENU(wxID_ABOUT,               BaseFrame::OnAbout)
wxEND_EVENT_TABLE()




BaseFrame::BaseFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(NULL, wxID_ANY, title, pos, size)
{

	// Create File Menu
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_AddCourseMenuSelect, "&Add Course...\tCtrl-G",
                     "Add a course to your GradeBook");
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



	wxBoxSizer *GridSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *CourseDropDownSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *TopSizer = new wxBoxSizer(wxVERTICAL);

	// Create Base Panel
    BaseFramePanel = new wxPanel(this, ID_GradeBookPanel, wxPoint(0,0), GBAPPSIZE, wxTAB_TRAVERSAL, "BaseFramePanel");
	BaseFramePanel->SetBackgroundColour(wxColour(char(255),char(255), char(255), char(0) ));

	// Add CourseDropDownList and GridView to Panel
	CourseDropDownList = new wxChoice(BaseFramePanel, ID_CourseDropDownList, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("CourseDropDownList"));
	GridView = new wxGrid( BaseFramePanel, ID_GridView, wxDefaultPosition, GBAPPSIZE, 0, "ID_GridView" );

	// Apply Sizer to CourseDropDownList and GridView
	TopSizer->Add(CourseDropDownList, 0, wxLEFT | wxTOP, 25);
	TopSizer->Add(GridView, 0, wxEXPAND | wxALL, 25);

	// Set TopSizer as primary sizer
	BaseFramePanel->SetSizer(TopSizer);


	PopulateCourseDropDownList();
	CreateStudentGridView();

}

// *** Modify grid to populate it with data pulled from DB ***
void BaseFrame::CreateStudentGridView()
{
	std::string str = "Homework_";
	char buffer[4];

	// Create Student Grid view. 30 rows and 10 columns
	// Pull from DB
	GridView->CreateGrid( 30, 250 );
	GridView->SetBackgroundColour(wxColour(char(255),char(255), char(255), char(0) ));
	GridView->Refresh();

	GridView->EnableDragColMove(true);
    GridView->EnableEditing(true);

	// Pull Data from DB
	for(int i = 0; i < 10; i++)
	{
		itoa(i+1, buffer, 10);
		str += buffer;
		GridView->SetColLabelValue(i,str);

		str = "Homework_";
	}

	// Pull Data from DB
	str = "Student_";
	for(int i = 0; i < 100; i++)
	{
		itoa(i+1, buffer, 10);
		str += buffer;
		GridView->SetRowLabelValue(i, str);
		str = "Student_";
	}
}




// *** Need to pull data from DB to populate Dropdown list ***
void BaseFrame::PopulateCourseDropDownList()
{
	std::string str = "Course_";

	// Static Data
	for(int i = 65; i < 83; i++)
	{
		str += char(i);
		CourseDropDownList->Append(str);
		str = "Course_";
	}

}

void BaseFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}
void BaseFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox( "Grade Book Application version 1.0.0",
                  "About", wxOK | wxICON_INFORMATION );
}
void BaseFrame::AddCourse(wxCommandEvent& event)
{
    wxLogMessage("Dialog Box Screen ... needs development ");
}