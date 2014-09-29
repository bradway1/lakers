#include "gbapp.h"
#include "gui\gbframe.h"
#include "sql/gbsql.h"

IMPLEMENT_APP(GBApp)

bool GBApp::OnInit() {

	GBFrame *pGBBase = new GBFrame("Grade Book", wxPoint(0,0), GBAPPSIZE);
	pGBBase->Show();
	SetTopWindow(pGBBase);

    return true;


}

