#ifndef _WIN_LOADER_H_
#define _WIN_LOADER_H_

#include "utils.h"



class WinLoader : public wxDialog{
	public:
		WinLoader(wxFrame *parent);

		//wxTextCtrl *textACR;
		//wxTextCtrl *textACC;

		void onQuit(wxCommandEvent & WXUNUSED(event));
		void loadACR(wxCommandEvent & WXUNUSED(event));
		void loadACC(wxCommandEvent & WXUNUSED(event));

		protected:
		DECLARE_EVENT_TABLE()
};

#endif // _WIN_LOADER_H_