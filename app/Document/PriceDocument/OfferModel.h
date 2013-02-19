#ifndef OFFERMODEL_H
#define OFFERMODEL_H

#include "PriceList.h"
#include "Document/DocumentModel.h"

class OfferModel : public DocumentModel
{

public:
    OfferModel();
    ~OfferModel();

    PriceList getOffer(QString symbol);
    void addOffer(PriceList list);
    void editOffer(PriceList newList);
    void removeOffer(QString symbol);
};

#endif // OFFERMODEL_H
