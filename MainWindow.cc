#include "MainWindow.h"

static void WindowDeleteEvent(GtkWidget *pWidget, GdkEvent *pEvent, gpointer pData)
{
	(*((MainWindow *)pData)->pCallback)();
}

MainWindow::MainWindow(WINDOW_DELETE_CALLBACK pSetCallback)
{
	// Set delete event handler
	pCallback = pSetCallback;
	
	// Create main window
    pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(pWindow), "DaddyMax");
	gtk_signal_connect(GTK_OBJECT(pWindow), "delete_event",
        GTK_SIGNAL_FUNC(WindowDeleteEvent), (gpointer)this);
}

MainWindow::~MainWindow()
{
    gtk_object_destroy(GTK_OBJECT(pWindow));
}

GtkWidget *MainWindow::GetWidget(void)
{
	return pWindow;
}

gboolean MainWindow::AddObject(DMXObject *pObject)
{
	gtk_container_add(GTK_CONTAINER(pWindow), pObject->GetWidget());
    pObject->Show();
	return TRUE;
}

gboolean MainWindow::RemoveObject(DMXObject *pObject)
{
	gtk_container_remove(GTK_CONTAINER(pWindow), pObject->GetWidget());
	return TRUE;
}