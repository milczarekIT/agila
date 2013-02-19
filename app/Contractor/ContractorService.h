#ifndef CONTRACTORSERVICE_H
#define CONTRACTORSERVICE_H

#include "Other/Exceptions/SQLException.h"
#include "Contractor/Contractor.h"
#include "Contractor/ContractorModel.h"
#include "Contractor/PhoneService.h"
#include "Contractor/ContractorCacheService.h"
#include "Other/Service.h"
class ContractorModel;

/**
  * @author Bartosz Milczarek
  */
class ContractorService : public Service
{
private:
    ContractorModel *model;
    PhoneService *phoneService;

    ContractorCacheService *cacheService;

    int insertedId;
    Contractor contractor;


    int addContractorWithoutTransaction(Contractor c);

    void getStandardData(int id);
    void getPhones(int id);

    void addStandardData(Contractor c);
    void addPhones(QVector<Phone> phones);

    void updateContractor(Contractor c);
    void editStandardData(Contractor c);
    void editPhones(int contractor, QVector<Phone> phones);

    void removeStandardData(int id);
    void removePhones(int contractor);
public:
    ContractorService();
    ~ContractorService();

    QVector<Contractor> getContractors();
    Contractor getContractor(int id);
    int addContractor(Contractor c);
    void editContractor(Contractor c);
    void removeContractor(int id);
};

#endif // CONTRACTORSERVICE_H
