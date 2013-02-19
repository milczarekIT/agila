#ifndef CONTRACTORADDITIONALTYPEIDMODEL_H
#define CONTRACTORADDITIONALTYPEIDMODEL_H

#include "Database/Model.h"
#include "Other/SimpleStructure.h"

class ContractorAdditionalTypeIdModel : public Model
{
public:
    ContractorAdditionalTypeIdModel();
    ~ContractorAdditionalTypeIdModel();

    QVector<SimpleStructure> getTypeIds();
    SimpleStructure getTypeId(int id);
};

#endif // CONTRACTORADDITIONALTYPEIDMODEL_H
