#ifndef _WIN_LOADER_H_
#define _WIN_LOADER_H_

#include "utils.h"
#include "gridPanel.h"
#include "pickPanel.h"
 
class WinLoader : public wxDialog{ 
	public:
		WinLoader(wxFrame *parent, gridPanel *grilles, pickPanel *picker);

		gridPanel *grid;
		pickPanel *pick;

		//wxTextCtrl *textACR;
		//wxTextCtrl *textACC;
		wxString *acr;
		wxString *acc;

		wxTextCtrl *textCharg;

		void OnQuit(wxCommandEvent & WXUNUSED(event));
		void onValid(wxCommandEvent & WXUNUSED(event));
		void loadACR(wxCommandEvent & WXUNUSED(event));
		void loadACC(wxCommandEvent & WXUNUSED(event));

		protected:
		DECLARE_EVENT_TABLE()
};
#endif // _WIN_LOADER_H_