#include "TableViewStandardMenu.h"

TableViewStandardMenu::TableViewStandardMenu()
{
    createActions();
    createMenu();
}

TableViewStandardMenu::~TableViewStandardMenu()
{
    delete menuStandard;
}

void TableViewStandardMenu::createActions()
{
    actionDel = new QAction("Usuń",this);
    actionDel->setShortcut(Qt::CTRL+Qt::Key_D);
    actionDel->setStatusTip("Usuń dokument");

    actionEdit = new QAction("Edytuj",this);
    actionEdit->setShortcut(Qt::CTRL+Qt::Key_E);
    actionEdit->setStatusTip("Edytuj dokument");

    actionAdd = new QAction("Dodaj",this);
    actionAdd->setShortcuts(QKeySequence::New);
    actionAdd->setStatusTip("Dodaj");

    actionPrintDoc = new QAction("Drukuj dokument",this);
    actionPrintDoc->setShortcut(Qt::CTRL+Qt::Key_P);
    actionPrintDoc->setStatusTip("Drukuj dokument");
}

void TableViewStandardMenu::createMenu()
{
    menuStandard = new QMenu();
    menuStandard->addAction(actionDel);
    menuStandard->addAction(actionEdit);
    menuStandard->addAction(actionAdd);
    menuStandard->addAction(actionPrintDoc);

}

QAction* TableViewStandardMenu::getActionEdit()
{
    return this->actionEdit;
}
QAction* TableViewStandardMenu::getActionDel()
{
    return this->actionDel;
}
QAction* TableViewStandardMenu::getActionAdd()
{
    return this->actionAdd;
}
QAction* TableViewStandardMenu::getActionPrintDoc()
{
    return this->actionPrintDoc;
}
QMenu* TableViewStandardMenu::getStandardMenu()
{
    return this->menuStandard;
}
void TableViewStandardMenu::removeActions()
{
   menuStandard->removeAction(actionPrintDoc);
}

void TableViewStandardMenu::exec(QContextMenuEvent *event)
{
    menuStandard->exec(event->globalPos());
}

