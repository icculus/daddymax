#include "MainNotebook.h"

MainNotebook::MainNotebook()
{
    // Create display widget
    pNotebook = gtk_notebook_new();
}

MainNotebook::~MainNotebook()
{
    gtk_object_destroy(GTK_OBJECT(pNotebook));
}

GtkWidget *MainNotebook::GetWidget(void)
{
	return pNotebook;
}
					 
gboolean MainNotebook::AddObject(DMXObject *pObject)
{
	return AddObjectWithLabel(pObject, gtk_label_new(""));
}

gboolean MainNotebook::RemoveObject(DMXObject *pObject)
{
	/***DO SOMETHING HERE***/
	return FALSE;
}

gboolean MainNotebook::AddObjectWithLabel(DMXObject *pObject, GtkWidget *pLabel)
{
	gtk_notebook_append_page(GTK_NOTEBOOK(pNotebook), pObject->GetWidget(), pLabel);
	pObject->Show();
	return TRUE;
}