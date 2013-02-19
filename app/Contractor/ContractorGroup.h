#ifndef CONTRACTORGROUP_H
#define CONTRACTORGROUP_H

#include <QString>
#include "Other/SimpleStructure.h"

class ContractorGroup : public SimpleStructure
{
public:
    ContractorGroup();
    ContractorGroup(QString name);
    ContractorGroup(int id, QString name);

    int operator ==(ContractorGroup cg);

};

#endif
