#ifndef MAINTABSALEITEM_H
#define MAINTABSALEITEM_H

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
#include "Main/MainTabSaleItemController.h"
#include "Main/MainTabDocumentFilterWidget.h"
class MainTabSaleItemController;

class MainTabSaleItem : public MainTabDocumentItem
{

private:
    QComboBox *buttons;
    Button *editSale;
    Button *deleteSale;
    MainTabSaleItemController *controller;
    void setInterface();
    void setConnections();
    void setMenuConnections();
    ButtonsList *createButtonsBox();

public:
    MainTabSaleItem(MainTabSaleItemController *controller);
    Button *getEditSale();
    Button *getDeleteSale();
};

#endif // MAINTABSALEITEM_H
