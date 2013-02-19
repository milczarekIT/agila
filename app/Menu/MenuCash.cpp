#include "MenuCash.h"

MenuCash::MenuCash(QString name)
{
    this->name=name;
    createActions();
    createMenu();
}

MenuCash::~MenuCash()
{
    delete menuCash;
}

void MenuCash::createActions()
{
    actionDocumentKPAdd = new QAction("Dokument KP",this);
    actionDocumentKWAdd = new QAction("Dokument KW",this);
}

void MenuCash::createMenu()
{
menuCash = new QMenu(name);
menuCash->addAction(this->actionDocumentKPAdd);
menuCash->addAction(this->actionDocumentKWAdd);
}

QMenu* MenuCash::getMenuCash()
{
    return this->menuCash;
}

QAction* MenuCash::getActionKPAdd(){return this->actionDocumentKPAdd;}
QAction* MenuCash::getActionKWAdd(){return this->actionDocumentKWAdd;}
