#ifndef CONTRACTORMODEL_H
#define CONTRACTORMODEL_H

#include <QVector>
#include "Database/Model.h"
#include "Database/Database.h"
#include "Contractor/Contractor.h"
#include "Contractor/ContractorGroupModel.h"
#include "Contractor/SOMModel.h"
#include "Contractor/PhoneModel.h"
#include "Contractor/ContractorTVDisplayer.h"
#include "Contractor/ContractorAdditionalTypeIdModel.h"
#include "Settings/SettingsModel.h"
#include "Other/Exceptions/SQLException.h"


class ContractorModel : public Model
{
    ContractorAdditionalTypeIdModel *additionalIdModel;

public:
    ContractorModel();
    ~ContractorModel();

    QVector<Contractor> getContractors();
    Contractor getContractor(int id);
    int addContractor(Contractor c);
    void editContractor(Contractor c);
    void removeContractor(int id);
    void deactivateContractorInDb(int id);
};

#endif // CONTRACTORMODEL_H
