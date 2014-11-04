#include "gbapp.h"
#include "gui\views\gbframeview.h"

IMPLEMENT_APP(GBApp)

bool GBApp::OnInit() {
	GBFrameView *pGBBase = new GBFrameView("Grade Book", wxPoint(0,0), GBAPPSIZE);

	pGBBase->Show();

	SetTopWindow(pGBBase);

  return true;
}

