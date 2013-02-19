#ifndef TOPCONTRACTORSTVDISPLAYER_H
#define TOPCONTRACTORSTVDISPLAYER_H

#include "Other/TVDisplayer.h"
#include "Contractor/ContractorGroupModel.h"

class TopContractorsTVDisplayer : public TVDisplayer
{
    bool isContractorGroupColumn() const;
    bool isPriceColumn() const;

    QVariant displayContractorGroup() const;
    QVariant displayPrice() const;
public:
    TopContractorsTVDisplayer(const QModelIndex & index, int role, TVModel const* model);
    ~TopContractorsTVDisplayer();

    QVariant display() const;
};

#endif // TOPCONTRACTORSTVDISPLAYER_H
