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

    QWidget *parent;

     Button *currentInventory;
     Button *currentInventoryGroups;
     Button *unpaidSaleDocument;
     Button *unpaidPurchaseDocument;
     Button *unrealizedDocumentsZK;
     Button *unrealizedDocumentsZD;
     Button *missingGoods;
     Button *endingGoods;
     Button *orderedGoodsZK;
     Button *orderedGoodsZD;
     Button *bestSellerGoods;
     Button *bestBuyers;


     QScrollArea *scrollArea;
     QWidget *reportsList;
     QVBoxLayout *reportsLayout;

public:
    MainTabReportsItem(MainTabReportsItemController *controller, QWidget *parent = 0);

};

#endif // MAINTABREPORTSITEM_H
