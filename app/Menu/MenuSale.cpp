#include "MenuSale.h"

MenuSale::MenuSale(QString name)
{
    this->name=name;
    createActions();
    createMenu();
}

MenuSale::~MenuSale()
{
    delete menuSale;
}

void MenuSale::createActions()
{
    actionInvoiceAdd = new QAction("Dokument FV",this);
    actionDocumentPROAdd = new QAction("Dokument PRO",this);
    actionDocumentPIAdd = new QAction("Dokument PI",this);
    actionDocumentPAAdd = new QAction("Dokument PA",this);
    actionDocumentFMPAdd = new QAction("Dokument FMP",this);
    actionDocumentFMAdd = new QAction("Dokument FM",this);
    actionDocumentFKAdd = new QAction("Dokument FK",this);
    actionIssuedFK = new QAction("Wystaw fakture korekcyjną",this);
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Cash))
    {
    actionIssuedCashDocKP = new QAction("Wystaw dokument kasa przyjmie",this);
    actionIssuedCashDocKW = new QAction("Wystaw dokument kasa wyda",this);
    }

}

void MenuSale::createMenu()
{
 menuSale = new QMenu(name);
 menuSale->addAction(this->actionInvoiceAdd);
 menuSale->addAction(this->actionDocumentPROAdd);
 menuSale->addAction(this->actionDocumentPIAdd);
 menuSale->addAction(this->actionDocumentPAAdd);
 menuSale->addAction(this->actionDocumentFMPAdd);
 menuSale->addAction(this->actionDocumentFMAdd);
 menuSale->addAction(this->actionDocumentFKAdd);

}

void MenuSale::setName(QString name)
{
    menuSale->setTitle(name);
}

QMenu* MenuSale::getMenuSale()
{
    return this->menuSale;
}

QAction* MenuSale::getActionInvoiceAdd(){return this->actionInvoiceAdd;}
QAction* MenuSale::getActionFMPAdd(){return this->actionDocumentFMPAdd;}
QAction* MenuSale::getActionPROAdd(){return this->actionDocumentPROAdd;}
QAction* MenuSale::getActionPIAdd(){return this->actionDocumentPIAdd;}
QAction* MenuSale::getActionPAAdd(){return this->actionDocumentPAAdd;}
QAction* MenuSale::getActionFKAdd(){return this->actionDocumentFKAdd;}
QAction* MenuSale::getActionFMAdd(){return this->actionDocumentFMAdd;}
QAction* MenuSale::getActionIssuedFK(){return this->actionIssuedFK;}
QAction* MenuSale::getActionIssuedCashDocKP()
{
    return this->actionIssuedCashDocKP;
}
QAction* MenuSale::getActionIssuedCashDocKW(){return this->actionIssuedCashDocKW;}
