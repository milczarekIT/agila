#ifndef MAINTABORDERITEM_H
#define MAINTABORDERITEM_H

#include "Main/MainTabItem.h"
#include "Components/Button.h"
#include "Components/TableView.h"
#include "Components/ButtonsList.h"
#include "Main/MainTabDocumentItem.h"
#include "Main/MainTabOrderItemController.h"
#include "Document/SaleDocument/DocumentFMController.h"
class MainTabOrderItemController;

class MainTabOrderItem : public MainTabDocumentItem
{
private:
    QComboBox *buttons;
    Button *editOrder;
    Button *deleteOrder;
    MainTabOrderItemController *controller;
    void setInterface();
    void setConnections();
    void setMenu();
    void demoBlocker();
    ButtonsList *createButtonsBox();

public:
    MainTabOrderItem(MainTabOrderItemController *controller);

};

#endif // MAINTABORDERITEM_H
