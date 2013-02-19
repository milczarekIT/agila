#ifndef MAINTABGOODSITEM_H
#define MAINTABGOODSITEM_H

#include <QLabel>
#include <QString>
#include <QComboBox>
#include <QLineEdit>
#include "Components/Button.h"
#include "Main/MainTabItem.h"
#include "Components/TableView.h"
#include "Main/MainTabGoodsItemController.h"
class MainTabGoodsItemController;

class MainTabGoodsItem : public MainTabItem
{
    Q_OBJECT
private:
    Button *addGood;
    Button *editGood;
    Button *deleteGood;
    QComboBox *goodsGroup;
    QComboBox *priceLevel;
    QLineEdit *gFilterSymbol;
    QLineEdit *gFilterName;
    MainTabGoodsItemController *controller;
    void setInterface();
    void setConnections();
    void setMenu();

public:
    MainTabGoodsItem(MainTabGoodsItemController *controller);
    Button *getAddGood();
    Button *getEditGood();
    Button *getDeleteGood();
    QComboBox *getGoodsGroup();
    QComboBox *getPriceLevel();
    QComboBox *getGoodsType();
    QLineEdit *getGFilterSymbol();
    QLineEdit *getGFilterName();
};

#endif // MAINTABGOODSITEM_H
