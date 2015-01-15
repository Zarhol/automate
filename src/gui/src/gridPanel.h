#ifndef _GRID_PANEL_H_
#define _GRID_PANEL_H_

#include "utils.h"

class gridPanel: public wxPanel {
	public:
		gridPanel(wxPanel *Parent);

		wxColour *couleur;

		void setColour(wxColour *color);

		bool isMouseOverGrid();
		void getCellHoveredByMouse(long mouseX, long mouseY, long & x, long & y);
		//void zoom(int x1,int y1, int x2, int y2);
		
		void onPaint(wxPaintEvent& event);
		void onClick(wxMouseEvent& event);

	protected:
		DECLARE_EVENT_TABLE()
};
#endif // _GRID_PANEL_H_
