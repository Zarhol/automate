#ifndef _evt_H_
#define _evt_H_

/*
*	Définit les id des différents evenements de l'interface
*/

typedef enum evts {
	evt_quit = wxID_HIGHEST + 1,// evenement à lancer lorsque l'on veut fermer une fenêtre
	evt_loadRule,			// evenement à lancer lorsque l'on demande le chargement d'une règle qualconque (ouverture de la fenêtre des règles sans préférence)
	evt_editRule,			// evenement à lancer lorsque l'on demande l'edition d'une règle
	evt_createRule,			// evenement à lancer lorsque l'on demande la création d'une nouvelle règle
	evt_saveRule,			// evenement à lancer lorsque l'on demande la sauvegarde de l'état actuel de la grille
	evt_settings,			// evenement à lancer lorsque l'on demande l'affichage des préférences de l'utilisateur
	evt_togglePlay,			// evenement à lancer lorsque l'on demande le lancement de l'automate en lecture automatique ou sa mise en pause si il tourne déja
	evt_step,				// evenement à lancer lorsque l'on demande l'avancement d'un tour alors que l'automate est en pause
	evt_reload,				// evenement à lancer lorsque l'on demande le rechargement de l'automate actuel
	evt_moreSpeed,			// evenement à lancer lorsque l'on demande l'accélération de la lecture automatique
	evt_lessSpeed,			// evenement à lancer lorsque l'on demande la descelération de la lecture automatique
	evt_zoomIn,				// evenement à lancer lorsque l'on demande le zoom de la grille affichée
	evt_zoomOut,			// evenement à lancer lorsque l'on demande le dézoom de la grille affichée
	evt_zoomFit,			// evenement à lancer lorsque l'on demande le dimmensionnement optimal de la grille affichée
	evt_toggleGridDisplay,	// evenement à lancer lorsque l'on demande l'affichage ou non des lignes de la grille
	evt_undo,				// evenement à lancer lorsque l'on demande l'annulation de la dernière action
	evt_redo,				// evenement à lancer lorsque l'on demande la désannulation de la dernière action
	evt_about,				// evenement à lancer lorsque l'on demande l'affichage de la fenêtre de resneignement sur le logiciel
	evt_helpOnline,			// evenement à lancer lorsque l'on demande à accéder à l'aide en ligne
	evt_help,				// evenement à lancer lorsque l'on demande l'affichage de la fenêtre d'aide

	evt_select,				// evenement à lancer lorsque l'ont clique sur le selecteur 

	evt_ANY = -1			// tout évenement dont on ne veut pas capturer le résultat
} evts;

#endif // _evt_H_