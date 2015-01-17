#ifndef _WIN_MAIN_H_
#define _WIN_MAIN_H_

#include "utils.h"
#include "winAbout.h"
#include "winHelpOnline.h"
#include "winHelp.h"
#include "winEdit.h"
#include "gridPanel.h"
#include "pickPanel.h"
#include <wx/colordlg.h>

/*
*	Définit la fenêtre principale de l'application. Celle qui contient la grille elle même.
*/

class WinMain : public wxFrame {
	protected:
		bool play_; // vrai si en lecture, faux sinon
		
	public:
		WinMain(wxString const& title);

		void updateGrid(); // permet de rafraichir la grille affichée
		void quit(); // permet de fermer proprement la fenêtre en sauvegardant ce qu'il faut
		bool loadRule(); // permet de demander le chargement d'une règle puis de la charger
		void saveCurrentConfig(); // affiche une fenêtre qui propose à l'utilisateur de sauvegarder la configuration actuelle de la grille
		void openPreferences(); // affiche la fenête des préférences
		void editFile(wxString const& filepath = _T("")); // permet d'éditer le fichier voulu, ou d'en créer un si filepath est vide
		// retourne le choix de l'utilisateur quant à une location de sauvegarde et un nom de fichier
		wxString saveAs(wxString const& format = _T("*"), wxString const& root = _T(""), wxString const& filename = _T("unknown_name.txt"));
		void  selectFiles(wxArrayString & str, wxString const& format = _T(""), wxString const& root = _T("")); // demande à l'utilisateur de récupérer plusieurs fichiers et place leurs noms dans str
		wxString  selectFile(wxString const& format = _T(""), wxString const& root = _T("")); // même chose mais pour un seul fichier
		
		wxColor pickColor(); // demande à l'utilisateur de choisir une fenêtre
		void togglePlay(); // active ou désactive la lecture auto
		void nextStep(); // avance d'un état et update
		




		// méthode de réaction au events
		// les events dessous ne sont pas lancés lorsque l'evenement dans leur nom apparait, mais juste avant
		// que ce soit fait, afin d'en gérer les conséquences

		// ie : l'evenement associé à onQuit ne signifie pas qu'on a quitté, juste qu'il a été demandé qu'on quitte
		void onQuit					(wxCommandEvent & event);
		void onLoadRule				(wxCommandEvent & event);
		void onEditRule				(wxCommandEvent & event);
		void onSaveRule				(wxCommandEvent & event);
		void onSettings				(wxCommandEvent & event);
		void onPlay					(wxCommandEvent & event);
		void onPause				(wxCommandEvent & event);
		void onStep					(wxCommandEvent & event);
		void onReload				(wxCommandEvent & event);
		void onMoreSpeed			(wxCommandEvent & event);
		void onLessSpeed			(wxCommandEvent & event);
		void onZoomIn   			(wxCommandEvent & event);
		void onZoomOut				(wxCommandEvent & event);
		void onZoomFit				(wxCommandEvent & event);
		void onToggleGridDisplay	(wxCommandEvent & event);
		void onUndo					(wxCommandEvent & event);
		void onRedo					(wxCommandEvent & event);
		void onAbout				(wxCommandEvent & event);
		void onHelpOnline			(wxCommandEvent & event);
		void onHelp					(wxCommandEvent & event);


	protected:
		void loadToolBar();
		void loadMenuBar();
		DECLARE_EVENT_TABLE()
};

#endif // _WIN_MAIN_H_