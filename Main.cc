#include <gtk/gtk.h>
#include "MainWindow.h"
#include "MainNotebook.h"
#include "LightingBoard.h"
#include "Stage.h"
#include "MainMenu.h"

MainWindow *pMainWnd;
MainMenu *pMainMenu;
MainNotebook *pNotebook;
LightingBoard *pBoard;
Stage *pStage;
GtkWidget *pBoardLabel;
GtkWidget *pStageLabel;

void MainWindowDeleteEvent()
{
	delete pStage;
	delete pBoard;
	delete pNotebook;
	delete pMainMenu;
	delete pMainWnd;
	
	gtk_main_quit();
}

void InitializeInterface()
{
	pMainWnd = new MainWindow(&MainWindowDeleteEvent);
	pNotebook = new MainNotebook();
	pBoard = new LightingBoard();
	pStage = new Stage();
	pMainMenu = new MainMenu();

    pMainWnd->AddObject(pMainMenu);
	pMainWnd->AddObject(pNotebook);

    pBoardLabel = gtk_label_new("Lighting Board");
    pStageLabel = gtk_label_new("Stage");
	pNotebook->AddObjectWithLabel(pBoard, pBoardLabel);
    pNotebook->AddObjectWithLabel(pStage, pStageLabel);

	pMainWnd->Show();
}

// This is where it all begins
int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);         // Initialize GTK widget library
    InitializeInterface();          // Load our GUI application
                                    // Stay here until we're notified that the
                                    //  GUI is finished.
    gtk_main();

    return 1;
}