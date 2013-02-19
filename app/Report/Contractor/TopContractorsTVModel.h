#ifndef TOPCONTRACTORSTVMODEL_H
#define TOPCONTRACTORSTVMODEL_H

#include "Database/TVModel.h"
#include "Contractor/Contractor.h"
#include "Report/Contractor/TopContractorsTVDisplayer.h"

class TopContractorsTVModel : public TVModel
{
    int limit;
    QString fromDateFilter;
    QString toDateFilter;
    void initHeaders();
protected:
     QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
public:
     TopContractorsTVModel();

    void getData();

    void setListLimitFilter(int limit);
    void setDateFromFilter(QDate fromDate);
    void setDateToFilter(QDate toDate);
};

#endif // TOPCONTRACTORSTVMODEL_H
