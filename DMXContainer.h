#ifndef INCLUDE_DMXCONTAINER
#define INCLUDE_DMXCONTAINER

#include <gtk/gtk.h>
#include "DMXObject.h"

class DMXContainer:public DMXObject
{
public:
	virtual gboolean AddObject(DMXObject *pObject)=0;
	virtual gboolean RemoveObject(DMXObject *pObject)=0;
private:
};
#endif