#include "Stage.h"

Stage::Stage()
{
    // Create display widget
	pScrollWindow = gtk_scrolled_window_new((GtkAdjustment*)NULL,
											(GtkAdjustment*)NULL);
	pBox = gtk_hbox_new(FALSE, 0);
		
    // Automatically show and hide scroll bars as needed
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(pScrollWindow),
	    GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(pScrollWindow),
										  pBox);
    gtk_widget_show(pBox);
}

Stage::~Stage()
{
	gtk_object_destroy(GTK_OBJECT(pBox));
    gtk_object_destroy(GTK_OBJECT(pScrollWindow));
}

GtkWidget *Stage::GetWidget(void)
{
	return pScrollWindow;
}

gboolean Stage::AddObject(DMXObject *pObject)
{
	gtk_container_add(GTK_CONTAINER(pBox), pObject->GetWidget());
	pObject->Show();
	return TRUE;
}

gboolean Stage::RemoveObject(DMXObject *pObject)
{
	gtk_container_remove(GTK_CONTAINER(pBox), pObject->GetWidget());
	return TRUE;
}