#ifndef INCLUDE_MAINNOTEBOOK
#define INCLUDE_MAINNOTEBOOK

#include <gtk/gtk.h>
#include "LightingBoard.h"
#include "Stage.h"
#include "DMXContainer.h"

class MainNotebook:public DMXContainer
{
public:
    MainNotebook();
	~MainNotebook();
	GtkWidget *GetWidget(void);
	
	gboolean AddObject(DMXObject *pObject);
	gboolean RemoveObject(DMXObject *pObject);

	gboolean AddObjectWithLabel(DMXObject *pObject, GtkWidget *pLabel);
private:
	GtkWidget *pNotebook;
};
#endif