#ifndef INCLUDE_SLIDER
#define INCLUDE_SLIDER

#include <gtk/gtk.h>
#include "DMXObject.h"

class Slider:public DMXObject
{
public:
	Slider();
	~Slider();
	GtkWidget *GetWidget(void);

    GtkObject *pAdjustment;

	// ***TEMPORARY***
	void ShowBump(gboolean Show);
	void EnableBump(gboolean Enable);
	void ShowSlider(gboolean Show);
	void EnableSlider(gboolean Enable);
	gboolean SetMin(guint Min);
	gboolean SetMax(guint Max);
private:
	GtkWidget *pWidget;
	GtkWidget *pSlider;
	GtkWidget *pBumpUp;
	GtkWidget *pBumpDown;
};
#endif