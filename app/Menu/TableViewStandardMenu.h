#ifndef TABLEVIEWSTANDARDMENU_H
#define TABLEVIEWSTANDARDMENU_H

#include "Menu/Menu.h"

#include <QContextMenuEvent>
#include <QKeyEvent>

class TableViewStandardMenu : public Menu
{
public:
    TableViewStandardMenu();
    ~TableViewStandardMenu();
    QAction* getActionEdit();
    QAction* getActionDel();
    QAction* getActionAdd();
    QAction* getActionPrintDoc();
    QMenu* getStandardMenu();
    void exec(QContextMenuEvent *event);
    void removeActions();

protected:

void createMenu();
void createActions();
QAction* actionEdit;
QAction* actionDel;
QAction* actionAdd;
QAction* actionPrintDoc;
QMenu* menuStandard;
};

#endif // TABLEVIEWSTANDARDMENU_H
