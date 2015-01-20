#ifndef _WIN_EDIT_H_
#define _WIN_EDIT_H_

#include "utils.h"
#include <wx/stc/stc.h>


class WinEdit : public wxFrame{
	public:
		WinEdit(wxFrame *parent);

		wxStyledTextCtrl *text; //l'editeur de texte est en attribut
		wxTextCtrl *debug;
		wxString *path;

		void onNew(wxCommandEvent& event);
		void onLoad(wxCommandEvent& event);
		void onSave(wxCommandEvent& event);
		void onDebug(wxCommandEvent& event);


		protected:
		void loadToolBar();
		DECLARE_EVENT_TABLE()
};

#endif // _WIN_EDIT_H_