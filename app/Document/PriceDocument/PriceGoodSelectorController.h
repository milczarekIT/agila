#ifndef PRICEGOODSELECTORCONTROLLER_H
#define PRICEGOODSELECTORCONTROLLER_H

#include "SelectionWindows/SelectGoodController.h"
#include "Goods/GoodsTVStandardItemModel.h"
class PriceGoodSelectorView;

class PriceGoodSelectorController : public SelectGoodController
{

private:
    GoodsTVStandardItemModel *goodsTVStandardModel;
    void setTableItemsChecked(Qt::CheckState  action);

protected:
    void initGoodsTable();

public:
    PriceGoodSelectorController(QWidget* parent, QString symbol);
    ~PriceGoodSelectorController();
    QVector<Goods> *getGoods();
    bool isChecked(int row);

public slots:
    void setGoodsNameFilter(QString text);
    void setGoodsSymbolFilter(QString text);
    void setGoodsGoodGroupFilter(int id);
    void setTaxForRRFilter(int idTax);
    void markAllItems(bool mark);
    void showingMarkAll(int count);
    void selectGoods();
};

#endif // PRICEGOODSELECTORCONTROLLER_H
