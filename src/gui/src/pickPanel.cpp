#include "pickPanel.h"

pickPanel::pickPanel (wxPanel *Parent)
					:wxPanel(Parent) {

}

void pickPanel::setGrid(gridPanel *grille){
    grid = grille;
}


void pickPanel::onResize(wxSizeEvent& event){


	wxSize taille = GetSize();
	wxListCtrl *list = new wxListCtrl(this, evt_select, wxDefaultPosition,taille,wxLC_REPORT | wxLC_NO_HEADER);
 	
 	
    wxListItem col0; //créé la première colonne
    col0.SetId(0);
    col0.SetText( _("Couleur") );
    col0.SetWidth(taille.GetWidth()*1/5);
    list->InsertColumn(0, col0);

    wxListItem col1; //crée la deuxième colonne
    col1.SetId(1);
    col1.SetText( _("Nom d'état") );
    col1.SetWidth(taille.GetWidth()*4/5);
    list->InsertColumn(1, col1);
	
    wxListItem etat1;	//créé la première ligne
    etat1.SetId(0);
    list->InsertItem(0, etat1);
    list->SetItem(0,0,_T("Noir"));
    list->SetItem(0,1,_T("EtatNoir"));

    wxListItem etat2; //crée la deuxième ligne
    etat2.SetId(1);
    list->InsertItem(1,etat2);
    list->SetItem(1,0,_T("Blanc"));
    list->SetItem(1,1,_T("EtatBlanc"));

    
    list->SetBackgroundColour(wxColour(50,45,50));
    list->SetForegroundColour(wxColour(255,255,255));

	int x = taille.GetWidth();
	int y = taille.GetHeight();

	std::cout<<"x : "<< x <<" | y : "<< y <<std::endl;
	
}

void pickPanel::onSelect(wxListEvent& event){
	long a = event.GetIndex(); // renvoi l'evenement selectionné
	if( a == 0 ){
        wxColour *a = new wxColour(0,0,0); // creer une nouvelle couleur (a changer plus tard surement)
        grid->setColour(a); //règle la couleur quand on colorie
        std::cout<<"c'est noir !!"<<std::endl;
	}
	else if (a == 1){
        wxColour *b = new wxColour(255,255,255);
		grid->setColour(b);
        std::cout<<"c'est blanc !!"<<std::endl;
	}
	else{
		wxMessageBox(_T("ya un bug dans ltruc"), _T("BOOM !"));
	}
}

BEGIN_EVENT_TABLE(pickPanel, wxPanel)
	EVT_SIZE(pickPanel::onResize)
	EVT_LIST_ITEM_SELECTED(evt_select, pickPanel::onSelect)
END_EVENT_TABLE()
