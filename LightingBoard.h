#ifndef INCLUDE_LIGHTINGBOARD
#define INCLUDE_LIGHTINGBOARD

#include <gtk/gtk.h>
#include "Slider.h"
#include "DMXContainer.h"

class LightingBoard:public DMXContainer
{
public:
    LightingBoard();
	~LightingBoard();
    GtkWidget *GetWidget(void);
    gboolean AddObject(DMXObject *pObject);
	gboolean RemoveObject(DMXObject *pObject);
private:
	GtkWidget *pScrollWindow;
	GtkWidget *pBox;
};
#endif