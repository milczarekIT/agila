#include "MenuStore.h"

MenuStore::MenuStore(QString name)
{
    this->name=name;
    createActions();
    createMenu();
}

MenuStore::~MenuStore()
{
    delete menuStore;
}

void MenuStore::createActions()
{
    actionDocumentPZAdd = new QAction("Dokument PZ",this);
    actionDocumentWZAdd = new QAction("Dokument WZ",this);
    actionDocumentPWAdd = new QAction("Dokument PW",this);
    actionDocumentRWAdd = new QAction("Dokument RW",this);
    actionDocumentMMAdd = new QAction("Dokument MM",this);
}

void MenuStore::createMenu()
{
    menuStore = new QMenu(name);
    menuStore->addAction(this->actionDocumentPZAdd);
    menuStore->addAction(this->actionDocumentWZAdd);
    menuStore->addAction(this->actionDocumentPWAdd);
    menuStore->addAction(this->actionDocumentRWAdd);
    menuStore->addAction(this->actionDocumentMMAdd);

}

QMenu* MenuStore::getMenuStore()
{
    return this->menuStore;
}

QAction* MenuStore::getActionPZAdd(){return this->actionDocumentPZAdd;}
QAction* MenuStore::getActionWZAdd(){return this->actionDocumentWZAdd;}
QAction* MenuStore::getActionRWAdd(){return this->actionDocumentRWAdd;}
QAction* MenuStore::getActionPWAdd(){return this->actionDocumentPWAdd;}
QAction* MenuStore::getActionMMAdd(){return this->actionDocumentMMAdd;}
