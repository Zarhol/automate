#ifndef _PICK_PANEL_H_
#define _PICK_PANEL_H_

#include "utils.h"
#include <vector>

  
class pickPanel : public wxPanel { 
	public:

		pickPanel(wxPanel *Parent);

		wxListCtrl *list;

		void reset();

		std::vector<unsigned int> getStates();

		void onResize(wxSizeEvent& event);
		void onSelect(wxListEvent& event);

	protected:
		DECLARE_EVENT_TABLE()
};
#endif // _PICK_PANEL_H_
