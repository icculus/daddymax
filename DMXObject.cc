#include "DMXObject.h"

DMXObject::DMXObject()
{
}

DMXObject::~DMXObject()
{
}

void DMXObject::Show(void)
{
    gtk_widget_show(GetWidget());
}

void DMXObject::Hide(void)
{
    gtk_widget_hide(GetWidget());
}

GtkMenuItem *DMXObject::GetMenu(void)
{
    return NULL;
}