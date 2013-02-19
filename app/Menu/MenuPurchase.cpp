#include "MenuPurchase.h"

MenuPurchase::MenuPurchase(QString name)
{
    this->name=name;
    createActions();
    createMenu();
}

MenuPurchase::~MenuPurchase()
{
    delete menuPurchase;
}

void MenuPurchase::createActions()
{
    actionDocumentFZKAdd = new QAction("Dokument FZK",this);
    actionDocumentNKAdd = new QAction("Dokument NK",this);
    actionDocumentRRAdd = new QAction("Dokument RR",this);
    actionPurInvoiceAdd = new QAction("Dokument FZ",this);
    actionIssuedFZK = new QAction("Wystaw fakture korekcyjną",this);
    actionIssuedKW = new QAction("Wystaw dokument kasa wyda",this);

}

void MenuPurchase::createMenu()
{
    menuPurchase = new QMenu(name);
    menuPurchase->addAction(this->actionDocumentFZKAdd);
    menuPurchase->addAction(this->actionDocumentNKAdd);
    menuPurchase->addAction(this->actionDocumentRRAdd);
    menuPurchase->addAction(this->actionPurInvoiceAdd);

}

QMenu* MenuPurchase::getMenuPurchase()
{
    return this->menuPurchase;
}

QAction* MenuPurchase::getActionPurInvoiceAdd(){return this->actionPurInvoiceAdd;}
QAction* MenuPurchase::getActionRRAdd(){return this->actionDocumentRRAdd;}
QAction* MenuPurchase::getActionNKAdd(){return this->actionDocumentNKAdd;}
QAction* MenuPurchase::getActionFZKAdd(){return this->actionDocumentFZKAdd;}
QAction* MenuPurchase::getActionIssuedFZK(){return this->actionIssuedFZK;}
QAction* MenuPurchase::getActionIssuedKW(){return this->actionIssuedKW;}
