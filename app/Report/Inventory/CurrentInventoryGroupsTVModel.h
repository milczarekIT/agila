#ifndef CURRENTINVENTORYGROUPSTVMODEL_H
#define CURRENTINVENTORYGROUPSTVMODEL_H

#include <QString>
#include "Goods/Price.h"
#include "Database/TVModel.h"
#include "Report/Inventory/CurrentInventoryGroupsTVDisplayer.h"

class CurrentInventoryGroupsTVModel : public TVModel
{
    QString zeroQuantityFilter;

    void initHeaders();

protected:
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

public:
    CurrentInventoryGroupsTVModel();
    ~CurrentInventoryGroupsTVModel();

    void getData();

    Price getValue();

    void showWithZeroQuantityFilter();
    void dontShowWithZeroQuantityFilter();
};

#endif // CURRENTINVENTORYGROUPSTVMODEL_H
