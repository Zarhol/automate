#include "winMain.h"


WinMain::WinMain(wxString const& title)
				: wxFrame((wxFrame*)NULL, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE) {
	wxInitAllImageHandlers();
	
	// on charge les menus
	loadMenuBar();
	// la barre d'outils
	loadToolBar();
	
	CreateStatusBar();
	SetStatusText(_T("Bienvenue sur ACS !")); // pas forcément utile pour le moment, mais le deviendra


	Center();
	Maximize();

	// -------- partie qui initialise les panels --------------------------------

	wxPanel *panel = new wxPanel(this, wxID_ANY); //panel principal
	gridPanel *rightPanel = new gridPanel(panel); // le panel de droite, c'est la classe qui gère la grille
	pickPanel *leftPanel = new pickPanel(panel); // le panel de gauche, ce sera le picker

	leftPanel->setGrid(rightPanel);

	wxColour leftColour(50,45,50); //  Créé une couleur pour le panel de gauche, celui de droite sera la grille

	wxBoxSizer *sizer_horizontal = new wxBoxSizer(wxHORIZONTAL); //  créé un boxSizer, celui ci va permettre de mettre les deux 
	// panels l'un à côté de l'autre
	
	//ajoute les panels au boxSizer (nomPanel, taille prie, les endroit des bords, et la taille du bord)
	sizer_horizontal->Add(leftPanel, 1 ,wxALL | wxEXPAND, 5);
	sizer_horizontal->Add(rightPanel, 3 ,wxEXPAND | wxBOTTOM | wxRIGHT | wxTOP, 5);

	//Met le sizer dans le panel principal.
	panel->SetSizer(sizer_horizontal);

}

void WinMain::updateGrid() {
	/* à faire */
}

void WinMain::quit() {
	/* gérer les cas où il faut sauvegarder du contenu non suvegardé */
	Close();
}

bool WinMain::loadRule() {
	/* afficher la fenêtre de chargement d'une règle */
	/* tout est modal. Retourner la réussite du chargement ou pas */

	return true;
}

void WinMain::saveCurrentConfig() {
	/* va demander un nom de fichier à l'utilisateur puis sauvegarder la configuration acutelle de la grille */
}

void WinMain::openPreferences() {
	/* à faire */
}

void WinMain::editFile(wxString const& filepath) {
	/* affiche l'editeur de fichier */
}

wxString WinMain::saveAs(wxString const& format, wxString const& root, wxString const& filename) {
	wxFileDialog dialog(this, _T("Sauvegarder"), root, filename, format, wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	dialog.ShowModal();	
	return dialog.GetFilename();
}

void WinMain::selectFiles(wxArrayString & str, wxString const& format, wxString const& root) {
	wxFileDialog dialog(this, _T("Choix de fichiers"), root, _T(""), format, wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_MULTIPLE);
	dialog.ShowModal();
	dialog.GetFilenames(str);
}

wxString WinMain::selectFile(wxString const& format, wxString const& root) {
	wxFileDialog dialog(this, _T("Choix d'un fichier"), root, _T(""), format, wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	dialog.ShowModal();
	return dialog.GetFilename();
}

wxColor WinMain::pickColor() {
	wxColourDialog color(this); // **tain de notation à l'anglaise
	color.SetTitle(_T("Choix d'une couleur"));
	color.ShowModal();
	return color.GetColourData().GetColour();
}

void WinMain::togglePlay() {
	/* déactive les menus et bouton de play lorsque pause et inversement */
	/* à faire */
	play_ = !play_;
}
void WinMain::nextStep() {
	/* à faire */
}


/**************************************************************************/
/************************ EVENTS *****************************************/
/************************************************************************/

void WinMain::onQuit(wxCommandEvent &  WXUNUSED(event)) {
	quit();
}

void WinMain::onLoadRule(wxCommandEvent & WXUNUSED(event)) {
	if(loadRule()) {
		wxMessageBox(_T("Le chargement s'est déroulé sans encombre"), _T("Chargement réussi"));
	}
	else {		
		wxMessageBox(_T("Le chargement s'est déroulé sans encombre"), _T("Chargement réussi"));
	}
}

void WinMain::onEditRule(wxCommandEvent & WXUNUSED(event)) {
	wxMessageBox(_T("Edition d'une règle"), _T("Edition"));
}

void WinMain::onSaveRule(wxCommandEvent & WXUNUSED(event)) {
	wxMessageBox(_T("Contenu sauvegardé"), _T("Sauvegarde"));
}

void WinMain::onSettings(wxCommandEvent & WXUNUSED(event)) {
	openPreferences();
}

void WinMain::onPlay(wxCommandEvent & WXUNUSED(event)) {
	togglePlay(); // on part du principe que le toggle bloque bien les différentes options
}

void WinMain::onPause(wxCommandEvent & WXUNUSED(event)) {
	togglePlay();
}

void WinMain::onStep(wxCommandEvent & WXUNUSED(event)) {
	nextStep();
}

void WinMain::onReload(wxCommandEvent & WXUNUSED(event)) {
	/* à faire */
}

void WinMain::onMoreSpeed(wxCommandEvent & WXUNUSED(event)) {
	/* à faire */
}

void WinMain::onLessSpeed(wxCommandEvent & WXUNUSED(event)) {
	/* à faire */
}

void WinMain::onZoomIn(wxCommandEvent & WXUNUSED(event)) {
	/* à faire */
}

void WinMain::onZoomOut(wxCommandEvent & WXUNUSED(event)) {
	/* à faire */
}

void WinMain::onZoomFit(wxCommandEvent & WXUNUSED(event)) {
	/* à faire */
}

void WinMain::onToggleGridDisplay(wxCommandEvent & WXUNUSED(event)) {
	/* à faire */
}

void WinMain::onUndo(wxCommandEvent & WXUNUSED(event)) {
	/* à faire */
}

void WinMain::onRedo(wxCommandEvent & WXUNUSED(event)) {
	/* à faire */
}

void WinMain::onAbout(wxCommandEvent & WXUNUSED(event)) {
	wxFrame *about = new WinAbout(this);
	about->Show(true);
}

void WinMain::onHelpOnline(wxCommandEvent & WXUNUSED(event)) {
	wxFrame *helpOnline = new WinHelpOnline(this);
	helpOnline->Show(true);
}

void WinMain::onHelp(wxCommandEvent & WXUNUSED(event)) {
	wxFrame *help = new WinHelp(this);
	help->Show(true);
}

/**************************************************************************/
/************************ PROTECTED **************************************/
/************************************************************************/


void WinMain::loadMenuBar() {
	// création des menus
	wxMenu* menuFile = new wxMenu;
		menuFile->Append(evt_loadRule, _T("&Charger une règle\tCTRL+O"));
		menuFile->Append(evt_createRule, _T("&Nouvelle règle\tCTRL+N"));
		menuFile->Append(evt_editRule, _T("&Editer une règle\tCTRL+E"));

		menuFile->AppendSeparator();
		menuFile->Append(evt_settings, _T("&Préférences"));

		menuFile->AppendSeparator();
		menuFile->Append(evt_quit, _T("&Quitter\tCTRL+Q"));

	wxMenu* menuEdit = new wxMenu;
		menuEdit->Append(evt_undo, _T("&Annuler action\tCTRL+Z"));
		menuEdit->Append(evt_redo, _T("&Refaire action\tCTRL+Y"));

	wxMenu* menuCtrl = new wxMenu;
		menuCtrl->Append(evt_togglePlay, _T("&Démarrer\tEnter"));
		menuCtrl->Append(evt_togglePlay, _T("Mettre en &pause\tEnter"));
		menuCtrl->Append(evt_step, _T("Prochaine &itération\tSpace"));

		menuCtrl->AppendSeparator();
		menuCtrl->Append(evt_reload, _T("&Recharger"));

		menuCtrl->AppendSeparator();
		menuCtrl->Append(evt_moreSpeed, _T("&Accélérer\tRight"));
		menuCtrl->Append(evt_lessSpeed, _T("Ralentir\tLeft"));

	wxMenu* menuDisplay = new wxMenu;
		menuDisplay->Append(evt_zoomIn, _T("Zoomer\tUp"));
		menuDisplay->Append(evt_zoomOut, _T("Dézoomer\tDown"));
		menuDisplay->Append(evt_zoomFit, _T("Adapter\t")); // traduction pour fit ?

		menuDisplay->AppendSeparator();
		menuDisplay->AppendCheckItem(evt_toggleGridDisplay, _T("Afficher la grille"));

	wxMenu* menuHelp = new wxMenu;
		menuHelp->Append(evt_help, _T("Aide\tF1"));
		menuHelp->Append(evt_helpOnline, _T("Aide en ligne"));

		menuHelp->AppendSeparator();
		menuHelp->Append(evt_about, _T("À propos d'ACS"));

	wxMenuBar* menuBar = new wxMenuBar;
		menuBar->Append(menuFile, _T("&Fichiers"));
		menuBar->Append(menuEdit, _T("&Edition"));
		menuBar->Append(menuCtrl, _T("&Contrôles"));
		menuBar->Append(menuDisplay, _T("&Affichage"));
		menuBar->Append(menuHelp, _T("A&ide"));

	SetMenuBar(menuBar);
}

void WinMain::loadToolBar() {
	// déclaration et chargement des images :
	wxBitmap bmNew(_T("img/new.png"), wxBITMAP_TYPE_PNG);
	wxBitmap bmEdit(_T("img/edit.png"), wxBITMAP_TYPE_PNG);

	wxBitmap bmPlay(_T("img/play.png"), wxBITMAP_TYPE_PNG);
	wxBitmap bmPause(_T("img/pause.png"), wxBITMAP_TYPE_PNG);
	wxBitmap bmStep(_T("img/step.png"), wxBITMAP_TYPE_PNG);

	wxBitmap bmZoomIn(_T("img/zoomIn.png"), wxBITMAP_TYPE_PNG);
	wxBitmap bmZoomOut(_T("img/zoomOut.png"), wxBITMAP_TYPE_PNG);
	wxBitmap bmFit(_T("img/fit.png"), wxBITMAP_TYPE_PNG);


	wxToolBar* toolbar = CreateToolBar();
		// on crée les images
		wxBitmapButton* bbNew = new wxBitmapButton(toolbar, -1, bmNew);
		wxBitmapButton* bbEdit = new wxBitmapButton(toolbar, -1, bmEdit);
		wxBitmapButton* bbPlay = new wxBitmapButton(toolbar, -1, bmPlay);
		wxBitmapButton* bbPause = new wxBitmapButton(toolbar, -1, bmPause);
		wxBitmapButton* bbStep = new wxBitmapButton(toolbar, -1, bmStep);
		wxBitmapButton* bbZoomIn = new wxBitmapButton(toolbar, -1, bmZoomIn);
		wxBitmapButton* bbZoomOut = new wxBitmapButton(toolbar, -1, bmZoomOut);
		wxBitmapButton* bbFit = new wxBitmapButton(toolbar, -1, bmFit);

		// on les ajoute à la toolbar
		toolbar->AddControl(bbNew);
		toolbar->AddControl(bbEdit);

		toolbar->AddSeparator();
		toolbar->AddControl(bbPlay);
		toolbar->AddControl(bbPause);
		toolbar->AddControl(bbStep);

		toolbar->AddSeparator();
		toolbar->AddControl(bbZoomIn);
		toolbar->AddControl(bbZoomOut);
		toolbar->AddControl(bbFit);

}

/**************************************************************************/
/************************ EVENT TABLE ************************************/
/************************************************************************/


BEGIN_EVENT_TABLE(WinMain, wxFrame)
    EVT_MENU		(evt_quit, WinMain::onQuit) // lors de la demande de fermeture via le menu
    EVT_MENU		(evt_loadRule, WinMain::onLoadRule) // chargement via le menu
    EVT_MENU		(evt_about, WinMain::onAbout) // lorsque qu'on veut des infos supplémentaires
    EVT_MENU		(evt_helpOnline, WinMain::onHelpOnline)
    EVT_MENU		(evt_help, WinMain::onHelp)
END_EVENT_TABLE()
