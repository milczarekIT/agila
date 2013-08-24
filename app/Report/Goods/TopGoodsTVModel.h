#ifndef TOPGOODSTVMODEL_H
#define TOPGOODSTVMODEL_H

#include "Database/TVModel.h"
#include "Report/Goods/TopGoodsTVDisplayer.h"

class TopGoodsTVModel : public TVModel
{
    int limit;
    QString fromDateFilter;
    QString toDateFilter;
    void initHeaders();
protected:
     QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
public:
    TopGoodsTVModel();

    void getData();

    QVariant data(int row, int column, int role);

    void setListLimitFilter(int limit);
    void setDateFromFilter(QDate fromDate);
    void setDateToFilter(QDate toDate);
};

#endif // TOPGOODSTVMODEL_H
