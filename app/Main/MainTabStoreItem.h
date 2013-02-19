#ifndef MAINTABSTOREITEM_H
#define MAINTABSTOREITEM_H

#include <QLabel>
#include <QComboBox>
#include <QDateEdit>
#include "Main/MainTabItem.h"
#include "Components/Button.h"
#include "Components/DateEdit.h"
#include "Components/TableView.h"
#include "Components/ButtonsList.h"
#include "Main/MainTabDocumentItem.h"
#include "Main/MainTabStoreItemController.h"
class MainTabStoreItemController;

class MainTabStoreItem : public MainTabDocumentItem
{
private:
    QComboBox *buttons;
    Button *editStore;
    Button *deleteStore;
    DateEdit *storeFrom;
    DateEdit *storeTo;
    MainTabStoreItemController *controller;
    void setInterface();
    void setConnections();
    void setMenu();
    ButtonsList *createButtonsBox();

public:
    MainTabStoreItem(MainTabStoreItemController *controller);
};

#endif // MAINTABSTOREITEM_H
