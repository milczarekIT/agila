#ifndef ORDERDOCUMENTTVDISPLAYER_H
#define ORDERDOCUMENTTVDISPLAYER_H

#include "Other/TVDisplayer.h"
#include "Contractor/ContractorService.h"

class OrderDocumentTVDisplayer : public TVDisplayer
{
private:
    bool isSymbolColumn() const;
    bool isNameColumn() const;
    bool isValueColumn() const;

    QVariant displayValue() const;
    QVariant displayName() const;
    QVariant displaySymbol() const;
public:
    OrderDocumentTVDisplayer(const QModelIndex & index, int role, TVModel const* model);
    ~OrderDocumentTVDisplayer();

    QVariant display() const;
};

#endif // ORDERDOCUMENTTVDISPLAYER_H
