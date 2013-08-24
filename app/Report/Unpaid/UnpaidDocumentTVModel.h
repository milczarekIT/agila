#ifndef UNPAIDDOCUMENTTVMODEL_H
#define UNPAIDDOCUMENTTVMODEL_H

#include <QSqlQuery>
#include <QString>
#include "Goods/Price.h"
#include "Database/TVModel.h"
#include "Report/Unpaid/UnpaidDocumentTVDisplayer.h"
#include "Other/Application/ApplicationManager.h"

class UnpaidDocumentTVModel : public TVModel
{
    QString notOnTimeFilter;
    void initHeaders(); // @see initUnpaidSaleDocumentsHeaders(); & initUnpaidPurchaseDocumentsHeaders();
    void initUnpaidSaleDocumentsHeaders();
    void initUnpaidPurchaseDocumentsHeaders();
protected:
    QVariant data(const QModelIndex & index, int role) const;
public:
    UnpaidDocumentTVModel();
    ~UnpaidDocumentTVModel();

    QVariant data(int row, int column, int role);

    void getUnpaidSaleDocuments();
    Price getUnpaidSaleValue();

    void getUnpaidPurchaseDocuments();
    Price getUnpaidPurchaseDocumentsValue();

    void notOnTimeFilterOnly();
    void resetOnTimeFilter();
};

#endif // UNPAIDDOCUMENTTVMODEL_H
