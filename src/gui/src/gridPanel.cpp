#include "gridPanel.h"



gridPanel::gridPanel (wxPanel *Parent)
					:wxPanel(Parent) {

	couleur = new wxColour(255,255,255); //couleur de base pour remplir une case
}


void gridPanel::setColour(wxColour *color){ //methode qui modifie la couleur
	couleur = color;
}


bool gridPanel::isMouseOverGrid(){ //renvoi vrai si la souris est dans la grille, faux sinon.
	wxPoint pt = ScreenToClient(wxGetMousePosition()); //récupère l'emplacement de la souris
	wxSize taille = GetSize(); //récupère les info sur le panel

	if(pt.x<=0 || pt.y<=0 || pt.x>=taille.GetWidth() || pt.y >=taille.GetHeight()){ 
	//si les coordonnés de la souris sont en dehors de la grille, renvoi faux
		return false;
	}
	else{
		return true;
	}
}

void gridPanel::getCellHoveredByMouse(long mouseX, long mouseY, long & x, long & y){ 
	//méthode permettant d'envoyer les coordonnés de la case a remplir.

	x = mouseX/20;
	x = x *20;

	y = mouseY/20;
	y = y*20;
}

/*void gridPanel::zoom(int x1,int y1, int x2, int y2){
	wxMessageBox(_T("ca Zoooooomm"), _T("ZOOOOOOMMMM !"));
	std::cout<<"yolo !"<<std::endl;
}*/


void gridPanel::onPaint(wxPaintEvent& event) {
	wxPaintDC monDc(this); // créer un wxPaintDC

    wxBrush maBrush(wxColour(0,0,0),wxSOLID ); // creer un brush, celui ci permet de colorier en noire.

    monDc.SetBrush(maBrush); 

    wxSize taille = GetSize();  // récupère des infos sur le panel

    int h = taille.GetHeight(); // récupère la hauteur
    int w = taille.GetWidth(); // récupère la largeur

    monDc.DrawRectangle(0,0,w,h); //dessine le fond de la grille
  
    wxColour maCouleur(100,100,100); //créé une couleur
    wxPen monCrayon(maCouleur,1,wxSOLID); //l'applique sur le stylo
    monDc.SetPen(monCrayon);


    for(int i = 20; i < w; i += 20){ //boucle qui dessine la grille
    	monDc.DrawLine(i,0,i,h);
    }
    for(int i=20; i<h;i+=20){
    	monDc.DrawLine(0,i,w,i);
    }
}

void gridPanel::onClick(wxMouseEvent& event) {
	
	do{

		if(isMouseOverGrid()){
			wxPoint pt = ScreenToClient( wxGetMousePosition() ); //récupère la position de la souris dans le panel
			long posX,posY;
			getCellHoveredByMouse(pt.x,pt.y,posX,posY); //renvoi les valeurs x et y pour remplir une case sur posX et posY

			wxPaintDC monDc(this);
			wxBrush maBrush(*couleur ,wxSOLID );  // brush rempli la case d'une couleur
			monDc.SetBrush(maBrush);

			wxColour maCouleur(100,100,100); 
		    wxPen monCrayon(maCouleur,1,wxSOLID);

		    monDc.SetPen(monCrayon);

			monDc.DrawRectangle(posX,posY,21,21); //créé un carré qui rempli une case de la grille (actuellement en blanc)	
		}

		
	}while(wxGetMouseState().LeftDown()); //boucle tant que le bouton gauche de la souris est enfoncé

}

BEGIN_EVENT_TABLE(gridPanel, wxPanel)
	EVT_PAINT		(gridPanel::onPaint) //dessine la grille
	EVT_LEFT_DOWN	(gridPanel::onClick) //se lance lorsqu'on clic dans la grille et colore la case pointée
END_EVENT_TABLE()


