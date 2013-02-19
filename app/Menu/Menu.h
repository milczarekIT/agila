#ifndef MENU_H
#define MENU_H

#include <QAction>
#include <QMenu>
#include <QObject>

class Menu : public QObject
{

public:
    Menu();
    virtual void createMenu() = 0;
    virtual void createActions() = 0;

};

#endif // MENU_H
