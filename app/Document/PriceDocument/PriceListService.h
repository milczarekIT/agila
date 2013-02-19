#ifndef PRICELISTSERVICE_H
#define PRICELISTSERVICE_H

#include "Document/DocumentService.h"
#include "Document/PriceDocument/PriceListModel.h"

class PriceListService : public DocumentService
{
private:
    PriceListModel *model;
    PriceList priceList;

public:
    PriceListService();
    ~PriceListService();
    PriceList getPriceList(QString symbol);
    void addPriceList(PriceList list);
    void editPriceList(PriceList newList);
    void removePriceList(QString symbol);
};

#endif // PRICELISTSERVICE_H
