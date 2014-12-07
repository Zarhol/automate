#include "winPanel.h"



winPanel::winPanel (wxPanel *Parent)
					:wxPanel(Parent) {


}

void winPanel::getCellHoveredByMouse(long mouseX, long mouseY, long & x, long & y){ 
	//méthode permettant d'envoyer les coordonnés de la case a remplir.

	x = mouseX/20;
	x = x *20;

	y = mouseY/20;
	y = y*20;
}


void winPanel::onPaint(wxPaintEvent& event) {
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

void winPanel::onClick(wxMouseEvent& event) {
	
	do{

		wxPoint pt = ScreenToClient( wxGetMousePosition() ); //récupère la position de la souris dans le panel
		long posX,posY;

		getCellHoveredByMouse(pt.x,pt.y,posX,posY); //renvoi les valeurs x et y pour remplir une case sur posX et posY

		wxPaintDC monDc(this); 
		wxBrush maBrush(wxColour(255,255,255),wxSOLID ); 
		wxColour maCouleur(100,100,100); 
	    wxPen monCrayon(maCouleur,1,wxSOLID);
	    monDc.SetPen(monCrayon);

		monDc.DrawRectangle(posX,posY,21,21); //créé un carré qui rempli une case de la grille (actuellement en blanc)
	}while(wxGetMouseState().LeftDown()); //boucle tant que le bouton gauche de la souris est enfoncé

}

BEGIN_EVENT_TABLE(winPanel, wxPanel)
	EVT_PAINT		(winPanel::onPaint) //dessine la grille
	EVT_LEFT_DOWN	(winPanel::onClick) //se lance lorsqu'on clic dans la grille et colore la case pointée
END_EVENT_TABLE()

