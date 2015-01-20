#ifndef _GRID_PANEL_H_
#define _GRID_PANEL_H_

#include "utils.h"
#include "pickPanel.h"
#include <vector>
 
class gridPanel: public wxPanel { 
	public:
		gridPanel(wxPanel *Parent, pickPanel *picker);

		wxColour *couleur;
		pickPanel *pick;

		void setColour(wxColour *color);

		//void zoomIn(Rect & win, float coef);
		//void zoomOut(Rect & win, float coef);

		bool isMouseOverGrid();
		void getCellHoveredByMouse(long mouseX, long mouseY, long & x, long & y);
		void getPos(int &posX, int &posY);
		void reset();
		void paint();
		void colorier(int posX, int posY);
		void play();
		
		void onPaint(wxPaintEvent& event);
		void onClick(wxMouseEvent& event);

	protected:
		DECLARE_EVENT_TABLE()
};
#endif // _GRID_PANEL_H_
