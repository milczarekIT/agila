#ifndef CONTRACTORGROUPMODEL_H
#define CONTRACTORGROUPMODEL_H

#include "Database/Model.h"
#include "Database/Database.h"
#include "Contractor/ContractorGroup.h"

class ContractorGroupModel : public Model
{
public:
    ContractorGroupModel();
    ~ContractorGroupModel();

    QVector<ContractorGroup> getContractorGroups();
    ContractorGroup getContractorGroup(int id);
    void addContractorGroup(ContractorGroup cg);
    void editContractorGroup(ContractorGroup cg);
    void removeContractorGroup(int id);
    void getContractorGroupsModel();
};

#endif // CONTRACTORGROUPMODEL_H
