#include "MainMenu.h"

MainMenu::MainMenu()
{
	pMenuBar = gtk_menu_bar_new();
	pMenu = gtk_menu_new();
}

MainMenu::~MainMenu()
{
    gtk_object_destroy(GTK_OBJECT(pMenuBar));
}

GtkWidget *MainMenu::GetWidget(void)
{
	return pMenuBar;
}

gboolean MainMenu::AddObject(DMXObject *pObject)
{
	return TRUE;
}

gboolean MainMenu::RemoveObject(DMXObject *pObject)
{
	return TRUE;
}