#include "ContractorGroup.h"

ContractorGroup::ContractorGroup()
{
    ContractorGroup::SimpleStructure(id, name);
}

ContractorGroup::ContractorGroup(QString name)
{
    this->name = name;
}

ContractorGroup::ContractorGroup(int id, QString name)
{
    this->setId(id);
    this->setName(name);
}

int ContractorGroup::operator ==(ContractorGroup cg)
{
    if(this->id != cg.getId())
        return 0;
    else if(this->name != cg.getName())
        return 0;
    else
        return 1;
}

