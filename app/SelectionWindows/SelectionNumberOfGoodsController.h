#ifndef SELECTIONNUMBEROFGOODSCONTROLLER_H
#define SELECTIONNUMBEROFGOODSCONTROLLER_H

#include "Goods/Goods.h"
#include "SelectionWindows/SelectionNumberOfGoodsView.h"

class SelectionNumberOfGoodsView;

class SelectionNumberOfGoodsController
{
private:
    SelectionNumberOfGoodsView* view;
    Goods* good;
    QString symbol;
public:
    SelectionNumberOfGoodsController(Goods* good,QString symbol);
    ~SelectionNumberOfGoodsController();

    int exec();
    SelectionNumberOfGoodsView* getView();
    Goods*getGood();
    QString getSymbol();
};

#endif // SELECTIONNUMBEROFGOODSCONTROLLER_H
