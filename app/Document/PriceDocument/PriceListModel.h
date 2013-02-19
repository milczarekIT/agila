#ifndef PRICELISTMODEL_H
#define PRICELISTMODEL_H

#include "PriceList.h"
#include "Document/DocumentModel.h"
class PriceListModel : public DocumentModel
{
private:

public:
    PriceListModel();
    ~PriceListModel();
    PriceList getPriceList(QString symbol);
    void addPriceList(PriceList list);
    void editPriceList(PriceList newList);
    void removePriceList(QString symbol);

};

#endif // PRICELISTMODEL_H
