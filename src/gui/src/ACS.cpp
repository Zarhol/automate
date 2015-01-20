#include "utils.h"
#include "ACS.h"
#include "winMain.h"
 
IMPLEMENT_APP(ACS); 

bool ACS::OnInit()
{
	wxFrame *gui = new WinMain(_T("ACS"));
    
    gui->Show(true);

    SetTopWindow(gui);

    return true;
}