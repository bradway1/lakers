#include "gbapp.h"
#include "Main.h"
#include "sql/gbsql.h"

IMPLEMENT_APP(GBApp)

bool GBApp::OnInit() {

	BaseFrame *gbBase = new BaseFrame("Grade Book", wxPoint(0,0), gbAppSize);
	//BaseFrame *gbBase = new BaseFrame(0);
	gbBase->Show();
	SetTopWindow(gbBase);

    return true;


}

