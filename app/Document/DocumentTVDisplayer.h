#ifndef DOCUMENTTVDISPLAYER_H
#define DOCUMENTTVDISPLAYER_H

#include "Other/TVDisplayer.h"
#include "Contractor/ContractorService.h"

class DocumentTVDisplayer : public TVDisplayer
{
private:
    bool isSymbolColumn() const;
    bool isNameColumn() const;
    bool isValueColumn() const;
    bool isDateColumn() const;
    bool isDocumentTypeColumn() const;

    QVariant displayValue() const;
    QVariant displayName() const;
    QVariant displaySymbol() const;
    QVariant displayDate()  const;
public:
    DocumentTVDisplayer(const QModelIndex & index, int role, TVModel const* model);
    ~DocumentTVDisplayer();

    QVariant display() const;
};

#endif // DOCUMENTTVDISPLAYER_H
