#ifndef PURCHASEDOCUMENTTVDISPLAYER_H
#define PURCHASEDOCUMENTTVDISPLAYER_H

#include "Other/TVDisplayer.h"
#include "Contractor/ContractorService.h"

/**
  * Displayer customowych danych dla modelu PurchaseDocument w TableView
  * @author Bartosz Milczarek
  */
class PurchaseDocumentTVDisplayer : public TVDisplayer
{
private:
    bool isSymbolColumn() const;
    bool isNameColumn() const;
    bool isValueColumn() const;
    bool isPurchaseDateColumn() const;

    QVariant displayValue() const;
    QVariant displayName() const;
    QVariant displaySymbol() const;
    QVariant displayPurchaseDate() const;
public:
    PurchaseDocumentTVDisplayer(const QModelIndex & index, int role, TVModel const* model);
    ~PurchaseDocumentTVDisplayer();

    QVariant display() const;
};

#endif // PURCHASEDOCUMENTTVDISPLAYER_H
