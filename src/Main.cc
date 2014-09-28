#include "Main.h"

wxBEGIN_EVENT_TABLE(BaseFrame, wxFrame)
    EVT_MENU(ID_AddCourseMenuSelect,   BaseFrame::AddCourse)
    EVT_MENU(wxID_EXIT,                BaseFrame::OnExit)
    EVT_MENU(wxID_ABOUT,               BaseFrame::OnAbout)
wxEND_EVENT_TABLE()


BaseFrame::BaseFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(NULL, wxID_ANY, title, pos, size)
{
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

	// Applies BaseBoxSizer to BaseFrame and applies BaseFramePanel inside BaseBoxSizer.
    wxBoxSizer *BaseBoxSizer = new wxBoxSizer(wxVERTICAL);
    BaseFramePanel = new wxPanel(this, ID_GradeBookPanel, wxPoint(0,0), GBAPPSIZE, wxTAB_TRAVERSAL, "BaseFramePanel");

    // Inserts CourseDropDownList inside BaseFramePanel
    CourseDropDownList = new wxChoice(BaseFramePanel, ID_CourseDropDownList, wxPoint(30,30), wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("CourseDropDownList"));
    BaseBoxSizer->Add(BaseFramePanel,0,0,0);
	BaseBoxSizer->Fit(this);

	PopulateCourseDropDownList();

}





void BaseFrame::PopulateCourseDropDownList()
{
	std::string str = "Course_";

	// Inside for loop we need to pull data
	// from DB and populate Dropdown list
	// with data from DB
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
    wxLogMessage("Dialog Box Screen Next ... needs development ");
}