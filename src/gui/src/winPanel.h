#ifndef _WIN_PANEL_H_
#define _WIN_PANEL_H_

#include "utils.h"

class winPanel: public wxPanel {
	public:
		winPanel(wxPanel *Parent);

		void getCellHoveredByMouse(long mouseX, long mouseY, long & x, long & y);
		void onPaint(wxPaintEvent& event);
		void onClick(wxMouseEvent& event);

	protected:
		DECLARE_EVENT_TABLE()
};
#endif // _WIN_PANEL_H_