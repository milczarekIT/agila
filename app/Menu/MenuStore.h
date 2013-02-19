#ifndef MENUSTORE_H
#define MENUSTORE_H

#include "Menu/Menu.h"

class MenuStore : public Menu
{
public:
    MenuStore(QString name);
    ~MenuStore();
    void createMenu();
    void createActions();
    QAction* getActionPZAdd();
    QAction* getActionWZAdd();
    QAction* getActionRWAdd();
    QAction* getActionPWAdd();
    QAction* getActionMMAdd();
    QMenu* getMenuStore();

private:
    QString name;
    QMenu* menuStore;
    QAction* actionDocumentPZAdd;
    QAction* actionDocumentWZAdd;
    QAction* actionDocumentRWAdd;
    QAction* actionDocumentPWAdd;
    QAction* actionDocumentMMAdd;
};

#endif // MENUSTORE_H
