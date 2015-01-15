#ifndef _PICK_PANEL_H_
#define _PICK_PANEL_H_

#include "utils.h"
#include "gridPanel.h"

class pickPanel : public wxPanel {
	public:

		gridPanel *grid;

		pickPanel(wxPanel *Parent);

		
		void setGrid(gridPanel *grille);

		void onResize(wxSizeEvent& event);
		void onSelect(wxListEvent& event);

	protected:
		DECLARE_EVENT_TABLE()
};
#endif // _PICK_PANEL_H_
