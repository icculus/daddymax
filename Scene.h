#ifndef INCLUDE_SCENE
#define INCLUDE_SCENE

#include <gtk/gtk.h>
#include "DMXContainer.h"

class Scene:public DMXContainer
{
public:
	Scene();
	~Scene();

    GtkWidget *GetWidget(void);
    gboolean AddObject(DMXObject *pObject);
	gboolean RemoveObject(DMXObject *pObject);
private:
	GtkWidget *pBox;
};
#endif