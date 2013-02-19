#ifndef MAINTABPRICEITEM_H
#define MAINTABPRICEITEM_H

#include <QLabel>
#include <QComboBox>
#include <QDateEdit>
#include <QStandardItemModel>
#include "Main/MainTabItem.h"
#include "Components/Button.h"
#include "Components/DateEdit.h"
#include "Components/TableView.h"
#include "Components/ButtonsList.h"
#include "Main/MainTabDocumentItem.h"
#include "Main/MainTabPriceItemController.h"
#include "Main/MainTabDocumentFilterWidget.h"
class MainTabPriceItemController;

class MainTabPriceItem : public MainTabDocumentItem
{

private:
    QComboBox *buttons;
    Button *edit;
    Button *del;
    MainTabPriceItemController *controller;
    void setInterface();
    void setConnections();
    void setMenuConnections();
    ButtonsList *createButtonsBox();

public:
    MainTabPriceItem(MainTabPriceItemController *controller);
    Button *getEditSale();
    Button *getDeleteSale();
};

#endif // MAINTABPRICEITEM_H
