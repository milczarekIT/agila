#ifndef MAINTABCASHITEM_H
#define MAINTABCASHITEM_H

#include "Main/MainTabItem.h"
#include "Components/Button.h"
#include "Components/TableView.h"
#include "Components/ButtonsList.h"
#include "Main/MainTabDocumentItem.h"
#include "Main/MainTabCashItemController.h"
class MainTabCashItemController;

class MainTabCashItem : public MainTabDocumentItem
{
    Q_OBJECT

private:
    QComboBox *buttons;
    Button *editDocument;
    Button *deleteDocument;
    MainTabCashItemController *controller;
    void setInterface();
    void setConnections();
    void setMenu();
    void demoBlocker();
    ButtonsList *createButtonsBox();

public:
    explicit MainTabCashItem(MainTabCashItemController *controller);

};

#endif // MAINTABCASHITEM_H
