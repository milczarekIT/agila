#ifndef MAINMENUCONTROLLER_H
#define MAINMENUCONTROLLER_H

#include <QWidget>
#include <QProgressDialog>
#include "Main/MainMenu.h"
#include "Tools/Help/HelpDialogView.h"
class MainMenu;

class MainMenuController : public QWidget
{
    Q_OBJECT
private:
    MainMenu *view;
    HelpDialogView *helpDialog;

public:
    MainMenuController();
    MainMenu *getView();

public slots:
    void showHelp();
};

#endif // MAINMENUCONTROLLER_H
