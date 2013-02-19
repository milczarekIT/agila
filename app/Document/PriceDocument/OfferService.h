#ifndef OFFERSERVICE_H
#define OFFERSERVICE_H

#include "Document/DocumentService.h"
#include "Document/PriceDocument/OfferModel.h"

class OfferService : public DocumentService
{
private:
    OfferModel *model;
    PriceList priceList;

public:
    OfferService();
    ~OfferService();

    PriceList getOffer(QString symbol);
    void addOffer(PriceList list);
    void editOffer(PriceList newList);
    void removeOffer(QString symbol);
};

#endif // OFFERSERVICE_H
