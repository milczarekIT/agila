#ifndef MAINMENU_H
#define MAINMENU_H

#include <QFrame>
#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include "Components/Button.h"
#include "Main/MainMenuController.h"
class MainMenuController;

class MainMenu : public QWidget
{
    Q_OBJECT
private:
    Button *file;
    Button *save;
    Button *print;
    Button *next;
    Button *back;
    Button *help;
    QLabel *logo;
    MainMenuController *controller;
    void setInterface();
public:
    explicit MainMenu(MainMenuController *controller);
    Button *getFile();
    Button *getSave();
    Button *getPrint();
    Button *getNext();
    Button *getBack();
    Button *getHelp();


};

#endif // MAINMENU_H
