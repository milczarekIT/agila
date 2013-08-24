#ifndef MAINTABREPORTSITEM_H
#define MAINTABREPORTSITEM_H

#include <QScrollArea>
#include <QGraphicsOpacityEffect>
#include "Main/MainTabItem.h"
#include "Components/Button.h"
#include "Components/TableView.h"
#include "Main/MainTabReportsItemController.h"
class MainTabReportsItemController;

class MainTabReportsItem : public MainTabItem
{

private:
    MainTabReportsItemController *controller;
    void setInterface();
    void setConnections();

    void addReportGroup(QString title, QList<QPushButton*> *buttons);
    QMenu* stdButtonMenu();

    QWidget *parent;

     Button *currentInventory;
     Button *currentInventoryGroups;
     Button *unpaidSaleDocuments;
     Button *unpaidPurchaseDocuments;
     Button *unrealizedDocumentsZK;
     Button *unrealizedDocumentsZD;
     Button *missingGoods;
     Button *endingGoods;
     Button *orderedGoodsZK;
     Button *orderedGoodsZD;
     Button *topGoods;
     Button *topContractors;


     QScrollArea *scrollArea;
     QWidget *reportsList;
     QVBoxLayout *reportsLayout;

public:
    MainTabReportsItem(MainTabReportsItemController *controller, QWidget *parent = 0);

    static QString ACTION_MENU_SHOW;
    static QString ACTION_MENU_GENERATE;

};

#endif // MAINTABREPORTSITEM_H
