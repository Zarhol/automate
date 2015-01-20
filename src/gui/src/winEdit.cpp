#include "winEdit.h"


WinEdit::WinEdit(wxFrame *parent)
		: wxFrame(parent, wxID_ANY, _T("Edition d'une règle")) {

		loadToolBar(); //charge la barre d'outil
		Center();
		
		wxPanel *panel = new wxPanel(this, wxID_ANY);
		path = new wxString(_T(""));

		//l'editeur de texte
		text = new wxStyledTextCtrl(panel, wxID_ANY,wxDefaultPosition, wxDefaultSize, 0 , _T("editeur"));

		//met les marges de gauche en place, la marge 0 correspond aux numéros de ligne
		text->SetMarginType(0, wxSTC_MARGIN_NUMBER);
		text->SetMarginWidth(0, 30);
		text->SetMarginWidth(1, 0);
		text->SetMarginWidth(2, 0);
		
		//c'est le texte du debuggueur, le texte est en readonly
		debug = new wxTextCtrl(panel, wxID_ANY,_T(""), wxDefaultPosition,wxDefaultSize, wxTE_READONLY | wxTE_MULTILINE,wxDefaultValidator, _T("debogueur"));
		
		//ajoute un texte au debuggueur
		debug->AppendText(_T("Debugguer...\n"));


		//créer un wxBoxSizer, ca permet de découper le panel
		wxBoxSizer *sizer_vertical = new wxBoxSizer(wxVERTICAL);


		sizer_vertical->Add(text, 3 ,wxEXPAND | wxLEFT| wxRIGHT | wxTOP, 5);
		sizer_vertical->Add(debug, 1 ,wxALL | wxEXPAND, 5);

		panel->SetSizer(sizer_vertical);
}


	void WinEdit::onNew(wxCommandEvent& event){
		if (text->GetModify()){
			if (wxMessageBox(_("Le fichier actuel n'a pas été sauvegardé, voulez vous continuer ?"), _("Confirmez Svp"),
				wxICON_QUESTION | wxYES_NO, this) == wxNO )
				return;
		}
		text->ClearAll(); //efface le contenu de l'editeur
	}
	void WinEdit::onLoad(wxCommandEvent& event){

		if (text->GetModify()){
			if (wxMessageBox(_("Le fichier actuel n'a pas été sauvegardé, voulez vous continuer ?"), _("Confirmez Svp"),
				wxICON_QUESTION | wxYES_NO, this) == wxNO )
				return;

		}
		
		wxFileDialog openFileDialog(this, _("Ouvrir un fichier"), _T(""), _T(""), _T("ACR and ACC files (*.acr;*.acc)|*.acr;*.acc"), wxFD_OPEN|wxFD_FILE_MUST_EXIST);
		//ouvre la fenêtre
		if (openFileDialog.ShowModal() == wxID_CANCEL)
			return; 

		//charge le contenu du fichier sur l'editeur
		bool test = text->LoadFile(openFileDialog.GetPath());
		if(test == false){
			wxMessageBox(_T("Il y a eu un problème au moment de charger le fichier"), _T("Echec chargement"));
			return;
		}
		path = new wxString(openFileDialog.GetPath());
	}
	void WinEdit::onSave(wxCommandEvent& event){
		wxFileDialog saveFileDialog(this, _("Sauvegarder"), _T(""), _T(""),_T("ACR and ACC files (*.acr;*.acc)|*.acr;*.acc"), wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
		if (saveFileDialog.ShowModal() == wxID_CANCEL)
			return;

		//sauvegarde le fichier
		bool test = text->SaveFile(saveFileDialog.GetPath());
		if(test == false){
			wxMessageBox(_T("Il y a eu un problème au moment de sauvegarder le fichier"), _T("Echec sauvagarde"));
			return;
		}
		path = new wxString(saveFileDialog.GetPath());
	}

	void WinEdit::onDebug(wxCommandEvent& event){
		if(text->GetModify()){
			wxMessageBox(_T("Il faut sauvegarder votre fichier avant de pouvoir le debugguer"), _T("Erreur"));
			return;
		}
		debug->Clear();
		Core *a = &Core::getInstance();
		boost::cmatch match;
		if(boost::regex_match(std::string(path->mb_str()).c_str(), match, boost::regex(".*\\.acr"))){
			std::string str = a->debug(std::string(path->mb_str()),type_rule);
			if(str.empty()){
				str = "Règle valide";
			}
			debug->AppendText(wxString(str.c_str(), wxConvUTF8));
		}
		else{ //ici couleur
			std::string str = a->debug(std::string(path->mb_str()),type_color);
			if(str.empty()){
				str = "Règle valide";
			}
			debug->AppendText(wxString(str.c_str(), wxConvUTF8));
		}

	}

	void WinEdit::loadToolBar(){
		//chargement des icones
		wxBitmap save(_T("img/save.png"), wxBITMAP_TYPE_PNG);
		wxBitmap load(_T("img/edit.png"), wxBITMAP_TYPE_PNG);
		wxBitmap New(_T("img/new.png"), wxBITMAP_TYPE_PNG);
		wxBitmap debog(_T("img/debog.png"), wxBITMAP_TYPE_PNG);

		//création de la barre d'outil
		wxToolBar *toolbar = CreateToolBar();
		toolbar->AddTool(evt_new,New,_T("Nouveau document"));
		toolbar->AddTool(evt_load,load,_T("Charger une règle"));
		toolbar->AddTool(evt_save,save,_T("sauvegarder une règle"));
		toolbar->AddTool(evt_debog,debog,_T("outil de debog"));
		toolbar->Realize();
 		}

	BEGIN_EVENT_TABLE(WinEdit, wxFrame)
		EVT_TOOL	(evt_new, WinEdit::onNew)
		EVT_TOOL	(evt_save, WinEdit::onSave)
		EVT_TOOL	(evt_load, WinEdit::onLoad)
		EVT_TOOL	(evt_debog, WinEdit::onDebug)
END_EVENT_TABLE()