#ifndef INCLUDE_STAGE
#define INCLUDE_STAGE

#include <gtk/gtk.h>
#include "DMXContainer.h"

class Stage:public DMXContainer
{
public:
	Stage();
    ~Stage();
	GtkWidget *GetWidget(void);
	
	gboolean AddObject(DMXObject *pObject);
	gboolean RemoveObject(DMXObject *pObject);
private:
	GtkWidget *pScrollWindow;
	GtkWidget *pBox;
};
#endif