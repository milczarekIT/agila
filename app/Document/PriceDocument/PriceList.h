#ifndef PRICELIST_H
#define PRICELIST_H

#include <QDate>
#include <QString>
#include "Document/Document.h"
#include "Document/DocumentPosition.h"

class PriceList : public Document
{

private:
    QString describe;
    QDate validFromDate;
    QDate validToDate;

public:
    PriceList();
    QString getDescribe();
    QDate getValidFromDate();
    QDate getValidToDate();
    void setDescribe(QString describe);
    void setValidFromDate(QDate validFromDate);
    void setValidToDate(QDate validToDate);
    QString toString();
    bool operator ==(PriceList list);
    bool areDocumentsPositionsEqual(QVector<DocumentPosition> dp);
};

#endif // PRICELIST_H
