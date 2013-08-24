#ifndef CURRENTINVENTORYTVMODEL_H
#define CURRENTINVENTORYTVMODEL_H

#include <QSqlQuery>
#include "Goods/Price.h"
#include "Database/TVModel.h"
#include "Report/Inventory/CurrentInventoryTVDisplayer.h"

class CurrentInventoryTVModel : public TVModel
{
    QString zeroQuantityFilter;

   void initHeaders();
protected:
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

public:
    CurrentInventoryTVModel();
    ~CurrentInventoryTVModel();

    void getData();
    Price getValue();

    QVariant data(int row, int column, int role = Qt::DisplayRole);

    void showWithZeroQuantityFilter();
    void dontShowWithZeroQuantityFilter();
};

#endif // CURRENTINVENTORYTVMODEL_H
