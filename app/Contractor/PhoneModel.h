#ifndef PHONEMODEL_H
#define PHONEMODEL_H

#include "Database/Model.h"
#include "Database/Database.h"
#include "Contractor/Phone.h"
#include "Other/Exceptions/SQLException.h"

/**
  * @author Bartosz Milczarek
  */
class PhoneModel : public Model
{
public:
    PhoneModel();
    ~PhoneModel();

    QVector<Phone> getPhones(int contractorId);
    void editPhone(int contractorId, Phone newPhone);
    void addPhone(int contractorId, Phone phone);
    void removePhone(int idPhone);
    void removeAllPhones(int contractor);
};

#endif // PHONEMODEL_H
