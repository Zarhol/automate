#include "gridPanel.h"



gridPanel::gridPanel (wxPanel *Parent, pickPanel *picker)
					:wxPanel(Parent) {

	couleur = new wxColour(0, 0, 0); //couleur de base pour remplir une case
	pick = picker;
	
}



void gridPanel::setColour(wxColour *color){ //methode qui modifie la couleur
	delete couleur;
	couleur = new wxColour(*color);
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

	x = mouseX/15;
	x = x *15;

	y = mouseY/15;
	y = y*15;
}

/*void gridPanel::zoomIn(Rect & win, float coef) { // zoomIn = le zoom normal
    long long width = (win.width-win.x)/coef;
    long long height = (win.height-win.y)/coef;
    win.x += (win.width-win.x-width)/2;
    win.y += (win.height-win.y-height)/2;
    win.width = width;
    win.height = height;
}

void gridPanel::zoomOut(Rect & win, float coef) { // zoomOut = le dézoom
    long long width = (win.width-win.x)*coef;
    long long height = (win.height-win.y)*coef;
    win.x += (win.width-win.x-width)/2;
    win.y += (win.height-win.y-height)/2;
    win.width = width;
    win.height = height;
}*/


void gridPanel::getPos( int &posX,int &posY){
	wxPoint pt = ScreenToClient( wxGetMousePosition());
	posX = pt.x /15;
	posY = pt.y /15;

}
 
void gridPanel::reset(){
	paint();
}

void gridPanel::paint(){
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


    for(int i = 15; i < w ; i += 15){ //boucle qui dessine la grille 
    	monDc.DrawLine(i,0,i,h);
    }
    for(int i = 15; i < h ; i += 15){
    	monDc.DrawLine(0,i,w,i);
    }
}

void gridPanel::colorier(int posX, int posY){

	posX = posX *16;
	posY = posY *16;


	wxPaintDC monDc(this);
	wxBrush maBrush(*couleur ,wxSOLID );  // brush rempli la case d'une couleur
	monDc.SetBrush(maBrush);
	wxColour maCouleur(100,100,100);
    wxPen monCrayon(maCouleur,1,wxSOLID);

    monDc.SetPen(monCrayon);
	monDc.DrawRectangle(posX,posY,16,16); 
}

void gridPanel::play(){
	Core *a = &Core::getInstance();
	Color cl;
	wxColour cellCol;
	a->update();
	paint(); //réinitialise la grille

	//à partir de là on lit les cellules à afficher et on utilise
	wxSize taille = GetSize();
	Core::const_iterator it = a->begin();
	Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.height = taille.GetX() / 16;
	rect.width = taille.GetY() / 16;
	Rect coord;
	for(; it != a->end(); ++it){

		if(a->isInRect(it,rect, &coord) ){

			if(it->second.hasColor()){ //modifie la couleur en fonction de la couleur de la case.
				cl = it->second.getColor();
				cellCol = wxColour(cl.r,cl.g,cl.b);
				setColour(&cellCol);
			}
			else {
				cellCol = wxColour(0, 0, 0);
				setColour(&cellCol);
			}
			colorier(coord.x, coord.y); //colorie la case

		}
	}
	

}



void gridPanel::onClick(wxMouseEvent& event) {
	Core *a = &Core::getInstance();

	long posX,posY;
	int coordX, coordY;
	int coordonneeX, coordonneeY = -1;
	wxPoint pt;
	Color cl;

	wxPaintDC monDc(this);
	//wxBrush maBrush(*couleur ,wxSOLID );  // brush rempli la case d'une couleur
	//monDc.SetBrush(maBrush);
	wxColour maCouleur(100,100,100);
	wxColour cellCol;
    wxPen monCrayon(maCouleur,1,wxSOLID); 

    monDc.SetPen(monCrayon);
	do{

		if(isMouseOverGrid()){
			pt = ScreenToClient( wxGetMousePosition() ); //récupère la position de la souris dans le panel

			getCellHoveredByMouse(pt.x,pt.y,posX,posY); //renvoi les valeurs x et y pour remplir une case sur posX et posY
			
			getPos(coordX, coordY);
			if(coordX != coordonneeX || coordY != coordonneeY){
				coordonneeX = coordX;
				coordonneeY = coordY;
				std::cout<<"x : "<<coordX<<" y : "<<coordY<<std::endl;
				std::vector<unsigned int> vec = pick->getStates();
				a->clear(coordonneeX,coordonneeY);
				a->set(coordonneeX,coordonneeY,vec);
				if(a->hasColor(coordonneeX,coordonneeY)){
					cl = a->getColor(coordonneeX, coordonneeY);
					cellCol = wxColour(cl.r,cl.g,cl.b);
					setColour(&cellCol);
				}
				else {
					cellCol = wxColour(0, 0, 0);
					setColour(&cellCol);
				}
				monDc.SetBrush(wxBrush(*couleur, wxSOLID));
			}



			monDc.DrawRectangle(posX,posY,16,16); //créé un carré qui rempli une case de la grille (actuellement en blanc)	
		}

		
	}while(wxGetMouseState().LeftDown()); //boucle tant que le bouton gauche de la souris est enfoncé

}


void gridPanel::onPaint(wxPaintEvent& event) {
	paint();
}



BEGIN_EVENT_TABLE(gridPanel, wxPanel)
	EVT_PAINT		(gridPanel::onPaint) //dessine la grille
	EVT_LEFT_DOWN	(gridPanel::onClick) //se lance lorsqu'on clic dans la grille et colore la case pointée
END_EVENT_TABLE()


