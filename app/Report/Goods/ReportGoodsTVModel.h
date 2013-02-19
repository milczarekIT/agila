#ifndef REPORTGOODSTVMODEL_H
#define REPORTGOODSTVMODEL_H

#include "Database/TVModel.h"
#include "Report/Goods/ReportGoodsTVDisplayer.h"

class ReportGoodsTVModel : public TVModel
{
    QString  quantityFilter;
    void initHeaders();
protected:
     QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
public:
    ReportGoodsTVModel();
    ~ReportGoodsTVModel();

    void getData();

    void setQuantityFilter(double value);
};

#endif // REPORTGOODSTVMODEL_H
