#ifndef INCLUDE_MAINMENU
#define INCLUDE_MAINMENU

#include <gtk/gtk.h>
#include "DMXContainer.h"

class MainMenu:public DMXContainer
{
public:
    MainMenu();
	~MainMenu();
	GtkWidget *GetWidget(void);
    gboolean AddObject(DMXObject *pObject);
	gboolean RemoveObject(DMXObject *pObject);
private:
	GtkWidget *pMenuBar;
};
#endif