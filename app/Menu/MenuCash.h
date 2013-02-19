#ifndef MENUCASH_H
#define MENUCASH_H

#include "Menu/Menu.h"

class MenuCash : public Menu
{
public:
    MenuCash(QString name);
    ~MenuCash();
    void createMenu();
    void createActions();
    QAction* getActionKPAdd();
    QAction* getActionKWAdd();
    QMenu* getMenuCash();

private:
QString name;
QMenu* menuCash;
QAction* actionDocumentKPAdd;
QAction* actionDocumentKWAdd;
};

#endif // MENUCASH_H
