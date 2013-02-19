#ifndef MENUSALE_H
#define MENUSALE_H

#include "Menu/Menu.h"
#include "Other/Application/ApplicationManager.h"

class MenuSale : public Menu
{
public:
    MenuSale(QString name);
    ~MenuSale();
    void createMenu();
    void createActions();
    void setName(QString name);
    QAction* getActionInvoiceAdd();
    QAction* getActionFMPAdd();
    QAction* getActionPROAdd();
    QAction* getActionPIAdd();
    QAction* getActionPAAdd();
    QAction* getActionFKAdd();
    QAction* getActionFMAdd();
    QAction* getActionIssuedFK();
    QAction* getActionIssuedCashDocKP();
    QAction* getActionIssuedCashDocKW();
    QMenu* getMenuSale();


private:
    QString name;
    QMenu* menuSale;
    QAction* actionInvoiceAdd;
    QAction* actionDocumentFMPAdd;
    QAction* actionDocumentPROAdd;
    QAction* actionDocumentPIAdd;
    QAction* actionDocumentPAAdd;
    QAction* actionDocumentFKAdd;
    QAction* actionDocumentFMAdd;
    QAction* actionIssuedFK;
    QAction* actionIssuedCashDocKP;
    QAction* actionIssuedCashDocKW;
};

#endif // MENUSALE_H
