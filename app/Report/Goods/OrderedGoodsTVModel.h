#ifndef ORDEREDGOODSTVMODEL_H
#define ORDEREDGOODSTVMODEL_H

#include "Database/TVModel.h"
#include "Report/Goods/OrderedGoodsTVDisplayer.h"

class OrderedGoodsTVModel : public TVModel
{
    QString type; // ZK/ZD - towary z zamówień od klientów (ZK), dostawców (ZD)
    QString priceNetColumnName;
    QString priceGrossColumnName;

    void initHeaders();
protected:
     QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
public:
    OrderedGoodsTVModel(QString type);

    QVariant data(int row, int column, int role);

    void getData();
};

#endif // ORDEREDGOODSTVMODEL_H
