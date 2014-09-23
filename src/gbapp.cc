#include "gbapp.h"
#include "Main.h"

#include "sql/gbsql.h"

IMPLEMENT_APP(GBApp)

bool GBApp::OnInit() {
	MyFrame *obj = new MyFrame("Test", wxPoint(50,50), wxSize(150,150));
	
	obj->Show();
	
    return true;
}
