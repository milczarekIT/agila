#ifndef MENUPURCHASE_H
#define MENUPURCHASE_H

#include "Menu/Menu.h"

class MenuPurchase : public Menu
{
public:
    MenuPurchase(QString name);
    ~MenuPurchase();
    void createMenu();
    void createActions();
    QAction* getActionPurInvoiceAdd();
    QAction* getActionRRAdd();
    QAction* getActionNKAdd();
    QAction* getActionFZKAdd();
    QAction* getActionIssuedFZK();
    QAction* getActionIssuedKW();
    QMenu* getMenuPurchase();

private:
    QString name;
    QMenu* menuPurchase;
    QAction* actionPurInvoiceAdd;
    QAction* actionDocumentRRAdd;
    QAction* actionDocumentNKAdd;
    QAction* actionDocumentFZKAdd;
    QAction* actionIssuedFZK;
    QAction* actionIssuedKW;
};

#endif // MENUPURCHASE_H
