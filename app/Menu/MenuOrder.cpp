#include "MenuOrder.h"

MenuOrder::MenuOrder(QString name)
{
    this->name=name;
    createActions();
    createMenu();
}

MenuOrder::~MenuOrder()
{
    delete menuOrder;
}

void MenuOrder::createActions()
{
    actionDocumentZDAdd = new QAction("Dokument ZD",this);
    actionDocumentZKAdd = new QAction("Dokument ZK",this);
    actionIssuedZD = new QAction("Wystaw fakturę zakupu",this);
}

void MenuOrder::createMenu()
{
    menuOrder = new QMenu(name);
    menuOrder->addAction(this->actionDocumentZDAdd);
    menuOrder->addAction(this->actionDocumentZKAdd);
}

QMenu* MenuOrder::getMenuOrder()
{
    return this->menuOrder;
}

QAction* MenuOrder::getActionZDAdd(){return this->actionDocumentZDAdd;}
QAction* MenuOrder::getActionZKAdd(){return this->actionDocumentZKAdd;}
QAction* MenuOrder::getActionIssuedZD(){return this->actionIssuedZD;}
