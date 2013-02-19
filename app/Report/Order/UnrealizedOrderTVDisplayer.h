#ifndef UNREALIZEDORDERTVDISPLAYER_H
#define UNREALIZEDORDERTVDISPLAYER_H

#include "Other/TVDisplayer.h"

class UnrealizedOrderTVDisplayer : public TVDisplayer
{
    bool isPriceColumn() const;
    bool isDateColumn() const;

    QVariant displayPrice() const;
public:
    UnrealizedOrderTVDisplayer(const QModelIndex &index, int role, const TVModel *model);

    QVariant display() const;
};

#endif // UNREALIZEDORDERTVDISPLAYER_H
