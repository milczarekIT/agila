#ifndef SALEDOCUMENTTVDISPLAYER_H
#define SALEDOCUMENTTVDISPLAYER_H

#include "Other/TVDisplayer.h"
#include "Contractor/ContractorService.h"

/**
  * Displayer customowych danych dla modelu SaleDocument w TableView
  * @author Bartosz Milczarek
  */
class SaleDocumentTVDisplayer : public TVDisplayer
{
private:
    bool isSymbolColumn() const;
    bool isNameColumn() const;
    bool isValueColumn() const;

    QVariant displayValue() const;
    QVariant displayName() const;
    QVariant displaySymbol() const;
public:
    SaleDocumentTVDisplayer(const QModelIndex & index, int role, TVModel const* model);
    ~SaleDocumentTVDisplayer();

    QVariant display() const;
};

#endif // SALEDOCUMENTTVDISPLAYER_H
