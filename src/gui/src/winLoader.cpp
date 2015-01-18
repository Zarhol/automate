#include "winLoader.h"


WinLoader::WinLoader(wxFrame *parent)
		: wxDialog(parent, wxID_ANY, _T("Chargement des règles"), wxDefaultPosition, wxSize(500,300)) {

		Center();

		//panel principale
		wxPanel *panel = new wxPanel(this, wxID_ANY);

		//va séparer le panel en 3 partie (les fichiers d'ouverture / la partie chargement, la partie bouton)
		wxBoxSizer *separe = new wxBoxSizer(wxVERTICAL);

		//créé un "tableau" de 2 ligne, 2 colonnes
		wxFlexGridSizer *grille = new wxFlexGridSizer(2,2,5,5);



		wxStaticText *staticACR = new wxStaticText(panel, -1, _T("Charger la règle :"));
		grille->Add(staticACR, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT);

		//ce qui est en commentaire devait permettre d'écrire le chemin du fichier quand on charge.
		//textACR = new wxTextCtrl(panel, -1, _T(""), wxDefaultPosition,wxSize(200,-1), wxTE_READONLY,wxDefaultValidator, _T("chargeRègle"));
		//grille->Add(textACR, 0, wxEXPAND);

		//bouton parcourir
		wxButton *butLoadACR = new wxButton(panel, evt_loadRuleACR, _T("Parcourir..."), wxPoint(20,20));
		grille->Add(butLoadACR, 0, wxEXPAND);


		//la nouvelle ligne commence à partir d'ici
		wxStaticText *staticACC = new wxStaticText(panel, -1, _T("Charger la règle de couleur :"));
		grille->Add(staticACC, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT);

		//textACC = new wxTextCtrl(panel, -1, _T(""), wxDefaultPosition,wxDefaultSize, wxTE_READONLY,wxDefaultValidator, _T("chargeRègleCouleur"));
		//grille->Add(textACC, 0, wxEXPAND);

		
		wxButton *butLoadACC = new wxButton(panel, evt_loadRuleACC, _T("Parcourir..."), wxPoint(20,20));
		grille->Add(butLoadACC, 0, wxEXPAND);

		grille->AddGrowableRow(2);

		separe->Add(grille, 1, wxALL | wxEXPAND, 5);

		//partis sur le chargement, quand on va charger la règle
		wxStaticBoxSizer *charg = new wxStaticBoxSizer(wxVERTICAL, panel, _T("Chargement :"));
		wxTextCtrl *textCharg = new wxTextCtrl(panel, -1, _T(""), wxDefaultPosition,wxDefaultSize, wxTE_READONLY | wxTE_MULTILINE,wxDefaultValidator, _T("chargeRègle"));
		charg->Add(textCharg, 1, wxALL |wxEXPAND, 5);

		separe->Add(charg, 1, wxALL | wxEXPAND, 5);
		

		//les boutons de validation et anulation
		wxBoxSizer *separeButton = new wxBoxSizer(wxHORIZONTAL);

		wxButton *butValid = new wxButton(panel, evt_loadRule, _T("Valider"), wxPoint(20,20));
		separeButton->Add(butValid, 0);

		separeButton->AddSpacer(5);

		wxButton *butCancel = new wxButton(panel, wxID_EXIT, _T("Annuler"), wxPoint(20,20));
		separeButton->Add(butCancel, 0);

		separe->Add(separeButton, 0, wxALIGN_RIGHT| wxALL, 5);

		panel->SetSizer(separe);
}
	void WinLoader::onQuit(wxCommandEvent & WXUNUSED(event)){
		//méthode d'évênement quand on appuie sur annuler
		Close(true);
	}

	void WinLoader::loadACR(wxCommandEvent & WXUNUSED(event)){
		//méthode pour parcourir les fichiers .ACR
		wxFileDialog openFileDialog(this, _("Ouvrir un fichier"), _T(""), _T(""), _T("ACR files (*.acr)|*.acr"), wxFD_OPEN|wxFD_FILE_MUST_EXIST);
		//ouvre la fenêtre
		if (openFileDialog.ShowModal() == wxID_CANCEL)
			return;

		//Ce qui est en commentaire en dessous permet d'afficher le chemin d'accès au fichier selectionné
		/*
		if(textACR->GetLineLength(0) <1){
			textACR->Clear();
		}
		textACR->AppendText(openFileDialog.GetPath());
		*/
	}
	void WinLoader::loadACC(wxCommandEvent & WXUNUSED(event)){
		//méthode pour parcourir les fichier .ACC

		wxFileDialog openFileDialog(this, _("Ouvrir un fichier"), _T(""), _T(""), _T("ACC files (*.acc)|*.acc"), wxFD_OPEN|wxFD_FILE_MUST_EXIST);
		//ouvre la fenêtre
		if (openFileDialog.ShowModal() == wxID_CANCEL)
			return;

		//Ce qui est en commentaire en dessous permet d'afficher le chemin d'accès au fichier selectionné
		/*
		if(textACC->GetLineLength(0) <1){
			textACC->Clear();
			std::cout<<"lol"<<std::endl;
		}
		textACC->AppendText(openFileDialog.GetPath());
		*/
	}

	BEGIN_EVENT_TABLE(WinLoader, wxDialog)
	EVT_BUTTON			(wxID_EXIT,WinLoader::onQuit)
	EVT_BUTTON			(evt_loadRuleACR,WinLoader::loadACR)
	EVT_BUTTON			(evt_loadRuleACC,WinLoader::loadACC)

END_EVENT_TABLE()