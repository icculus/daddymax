#include "Scene.h"

Scene::Scene()
{
	pBox = gtk_hbox_new(FALSE, 0);
}

Scene::~Scene()
{
	gtk_object_destroy(GTK_OBJECT(pBox));
}

GtkWidget *Scene::GetWidget(void)
{
	return pBox;
}

gboolean Scene::AddObject(DMXObject *pObject)
{
	gtk_container_add(GTK_CONTAINER(pBox), pObject->GetWidget());
	pObject->Show();
	return TRUE;
}

gboolean Scene::RemoveObject(DMXObject *pObject)
{
	gtk_container_remove(GTK_CONTAINER(pBox), pObject->GetWidget());
	return TRUE;
}