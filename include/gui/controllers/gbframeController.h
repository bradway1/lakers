#ifndef _GBFRAMECONTROLLER
#define _GBFRAMECONTROLLER



#include <stdlib.h>
#include <wx/wxprec.h>
#include <wx/panel.h>
#include <wx/grid.h>
#include <wx/editlbox.h>
#include <wx/listctrl.h>
#include <wx/event.h>
#include <wx/filepicker.h>
#include <wx/combobox.h>
#include "gui\views\gbdialogassessmentView.h"
#include "gui\views\gbdialogcourseView.h"

class GBFrameView;

class GBFrameController
{
public:
    GBFrameController(GBFrameView *view);
	// Events
    void AddCourse(wxCommandEvent& event);
    void ModifyAssignments(wxCommandEvent& event);
    void AssignmentSelected(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void NewCourseSelected(wxCommandEvent& event);


private:

	void PopulateCourseDropDownList();
	void CreateGridView();
	wxString GetCourseComboBoxSelection();


    GBFrameView 				*m_pMainFrameView;
    GBDialogAssessmentView		*m_pDialogAssessmentView;
	GBDialogCourseView			*m_pDialogCourse;

};


#endif