#ifndef GOODSTVMODEL_H
#define GOODSTVMODEL_H

#include "Goods/Goods.h"
#include "QStandardItemModel"
#include "Database/TVModel.h"
#include "Goods/GoodsFilters.h"
#include "Goods/GoodsTVDisplayer.h"

/**
  * TableViewModel dla contractora
  * @autor Bartosz Milczarek, Krzysztof Marjański
  */
class GoodsTVModel : public TVModel, public GoodsFilters
{
private:
    void initHeaders();

protected:
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

public:
    GoodsTVModel();
    ~GoodsTVModel();

    void sort ( int column, Qt::SortOrder order = Qt::AscendingOrder );

    /**
      * Przekazuje do modelu najważniejsze dane o wszystkich towarach/usługach
      * Dane w modelu: id, symbol, name, quantity, unit, tax, goodsGroup, priceANet, priceAGross, priceMagNet, priceMagGross
      * Nagłowek dla TableView jest ustawiany automatycznie (metoda getGoods() to robi)
      *
      */
    void getGoods();
    QStandardItemModel *getGoodsCustomModel();
    QStandardItem *createCheckedItem();
    void getGoodsForRR();
};

#endif // GOODSTVMODEL_H
