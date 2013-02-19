#ifndef MENUORDER_H
#define MENUORDER_H

#include "Menu/Menu.h"

class MenuOrder : public Menu
{
public:
    MenuOrder(QString name);
    ~MenuOrder();
    void createMenu();
    void createActions();
    QAction* getActionZDAdd();
    QAction* getActionZKAdd();
    QAction* getActionIssuedZD();
    QMenu* getMenuOrder();

private:
    QString name;
    QMenu* menuOrder;
    QAction* actionDocumentZDAdd;
    QAction* actionDocumentZKAdd;
    QAction* actionIssuedZD;
};

#endif // MENUORDER_H
