#ifndef INCLUDE_MAINWINDOW
#define INCLUDE_MAINWINDOW

#include <gtk/gtk.h>
#include "DMXContainer.h"

typedef void (*WINDOW_DELETE_CALLBACK)(void);

class MainWindow:public DMXContainer
{
public:
    MainWindow(WINDOW_DELETE_CALLBACK pSetCallback);
	~MainWindow();
	GtkWidget *GetWidget(void);
    gboolean AddObject(DMXObject *pObject);
	gboolean RemoveObject(DMXObject *pObject);

	WINDOW_DELETE_CALLBACK pCallback;
private:
	GtkWidget *pWindow;
};
#endif