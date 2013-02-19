#ifndef UNPAIDDOCUMENTTVDISPLAYER_H
#define UNPAIDDOCUMENTTVDISPLAYER_H

#include "Other/TVDisplayer.h"
#include "Goods/Price.h"

class UnpaidDocumentTVDisplayer : public TVDisplayer
{
    bool isPriceColumn() const;
    bool isDaysToPay() const;
    bool isDateColumn() const;

    QVariant displayPrice() const;
public:
    UnpaidDocumentTVDisplayer(const QModelIndex & index, int role, TVModel const* model);

    QVariant display() const;
};

#endif // UNPAIDDOCUMENTTVDISPLAYER_H
