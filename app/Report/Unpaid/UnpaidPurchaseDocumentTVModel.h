#ifndef UNPAIDPURCHASEDOCUMENTTVMODEL_H
#define UNPAIDPURCHASEDOCUMENTTVMODEL_H

#include <QSqlQuery>
#include <QString>
#include "Goods/Price.h"
#include "Database/TVModel.h"
#include "Report/Unpaid/UnpaidDocumentTVDisplayer.h"

class UnpaidPurchaseDocumentTVModel  : public TVModel
{
    QString notOnTimeFilter;
    void initHeaders();
protected:
    QVariant data(const QModelIndex & index, int role) const;
public:
    UnpaidPurchaseDocumentTVModel();
    ~UnpaidPurchaseDocumentTVModel();

    void getData();
    Price getValue();

    void initNotOnTimeFilterOnly();
};

#endif // UNPAIDPURCHASEDOCUMENTTVMODEL_H
