#include "Slider.h"

/* Event Handlers */
static void BumpUpEvent(GtkWidget *pWidget, GdkEvent *pEvent,
                        gpointer pData)
{
	// Set slider all the way up
	gtk_adjustment_set_value(GTK_ADJUSTMENT(((Slider *)pData)->pAdjustment),
							 100);
}

static void BumpDownEvent(GtkWidget *pWidget, GdkEvent *pEvent,
                          gpointer pData)
{
	// Set slider all the way up
	gtk_adjustment_set_value(GTK_ADJUSTMENT(((Slider *)pData)->pAdjustment),
							 0);
}

/* Class Members */
Slider::Slider()
{
    // Create components of the slider
	pWidget = gtk_vbox_new(FALSE, 0);
	pAdjustment = gtk_adjustment_new(100, 0, 100, 0.1, 1, 0);
	pSlider = gtk_vscale_new(GTK_ADJUSTMENT(pAdjustment));
	pBumpUp = gtk_button_new();
	pBumpDown = gtk_button_new();

	// Configure the slider
    gtk_scale_set_value_pos(GTK_SCALE(pSlider), GTK_POS_RIGHT);

	// Add events handlers
	gtk_signal_connect(GTK_OBJECT(pBumpUp), "button_release_event",
					   GTK_SIGNAL_FUNC(BumpUpEvent), (gpointer)this);
	gtk_signal_connect(GTK_OBJECT(pBumpDown), "button_release_event",
					   GTK_SIGNAL_FUNC(BumpDownEvent), (gpointer)this);
	
	// Insert widgets into main container widget
	gtk_box_pack_start(GTK_BOX(pWidget), pBumpUp, FALSE, FALSE, 0);
	gtk_box_pack_start_defaults(GTK_BOX(pWidget), pSlider);
	gtk_box_pack_start(GTK_BOX(pWidget), pBumpDown, FALSE, FALSE, 0);

	// Show widgets
	ShowBump(TRUE);
	ShowSlider(TRUE);
}

Slider::~Slider()
{
	gtk_object_destroy(GTK_OBJECT(pSlider));
	gtk_object_destroy(GTK_OBJECT(pBumpUp));
	gtk_object_destroy(GTK_OBJECT(pBumpDown));
	//***This doesn't work for some reason!?!?!***
	//gtk_object_destroy(pAdjustment);
	gtk_object_destroy(GTK_OBJECT(pWidget));
}

GtkWidget *Slider::GetWidget(void)
{
    return pWidget;
}

void Slider::ShowBump(gboolean Show)
{
	if(Show)
	{
		gtk_widget_show(pBumpUp);
		gtk_widget_show(pBumpDown);
	}
	else
	{
		gtk_widget_hide(pBumpUp);
		gtk_widget_hide(pBumpDown);
	}
}

void Slider::EnableBump(gboolean Enable)
{
}

void Slider::ShowSlider(gboolean Show)
{
	if(Show) gtk_widget_show(pSlider);
	else gtk_widget_hide(pSlider);
}

void Slider::EnableSlider(gboolean Enable)
{
}

gboolean Slider::SetMin(guint Min)
{
    return FALSE;
}

gboolean Slider::SetMax(guint Max)
{
    return FALSE;
}