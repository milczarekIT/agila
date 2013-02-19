#ifndef CONTRACTORTVDISPLAYER_H
#define CONTRACTORTVDISPLAYER_H

#include "Other/TVDisplayer.h"
#include "Contractor/ContractorGroupModel.h"

/**
  * Displayer customowych danych dla modelu Contractor w TableView
  * @author Bartosz Milczarek
  */
class ContractorTVDisplayer : public TVDisplayer
{
private:
    bool isContractorGroupColumn() const;
    QVariant displayContractorGroup() const;
public:
    ContractorTVDisplayer(const QModelIndex & index, int role, TVModel const* model);
    ~ContractorTVDisplayer();

    QVariant display() const;
};

#endif // CONTRACTORTVDISPLAYER_H
