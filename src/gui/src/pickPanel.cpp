#include "pickPanel.h"

pickPanel::pickPanel (wxPanel *Parent)
					:wxPanel(Parent) {
    wxSize taille = GetSize();
    list = new wxListCtrl(this, evt_select, wxDefaultPosition,taille,wxLC_REPORT | wxLC_NO_HEADER);
}
 

void pickPanel::reset(){
    std::cout << "reset" << std::endl;
    Core *a = &Core::getInstance();
    unsigned int stateCount = a->stateCount();
    wxSize taille = GetSize();
    
    delete list;
    list = new wxListCtrl(this, evt_select, wxDefaultPosition,taille,wxLC_REPORT | wxLC_NO_HEADER);

    wxListItem col1; //crée la deuxième colonne
    col1.SetId(0);
    col1.SetText( _("Nom d'état") );
    col1.SetWidth(taille.GetWidth());
    list->InsertColumn(0, col1);

            std::cout << stateCount << std::endl;
    for(unsigned int i = 0; i < stateCount; ++i){
        wxListItem etat; 
        etat.SetId(i);
        list->InsertItem(i,etat);

        std::cout << "i : " << i << std::endl;
        if(i >= stateCount) {
            std::cout << "mah" << std::endl;
            exit(1);
        }
        else {
            std::cout << "meyh" << std::endl;
        }
        list->SetItem(i,0,wxString(a->getStateName(i).c_str(),wxConvUTF8));
        std::cout<< a->getStateName(i) << std::endl; 
    }


    
    list->SetBackgroundColour(wxColour(50,45,50));
    list->SetForegroundColour(wxColour(255,255,255));

}

std::vector<unsigned int> pickPanel::getStates(){
    Core *a = &Core::getInstance();
    unsigned int stateCount = a->stateCount();
    std::vector<unsigned int> vec;
    long item = -1;
    while(1){
        item = list->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
        if(item == -1) break;
        vec.push_back(item);
    }
    return vec;
    
}


void pickPanel::onResize(wxSizeEvent& event){

	
}

void pickPanel::onSelect(wxListEvent& event){
	long a = event.GetIndex(); // renvoi l'evenement selectionné
    std::cout<<"élément : "<<a <<" sélectionné"<<std::endl;

}

BEGIN_EVENT_TABLE(pickPanel, wxPanel)
	EVT_SIZE(pickPanel::onResize)
	EVT_LIST_ITEM_SELECTED(evt_select, pickPanel::onSelect)
END_EVENT_TABLE()
