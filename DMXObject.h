#ifndef INCLUDE_DMXOBJECT
#define INCLUDE_DMXOBJECT

#include <gtk/gtk.h>

class DMXObject
{
public:
    DMXObject();
    virtual ~DMXObject();
	virtual GtkWidget *GetWidget(void)=0;
	virtual GtkMenuItem *GetMenu(void);
	void Show(void);
	void Hide(void);
private:
};
#endif