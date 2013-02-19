#ifndef PHONESERVICE_H
#define PHONESERVICE_H

#include "Other/Exceptions/SQLException.h"
#include "PhoneModel.h"

/**
  * @author Bartosz Milczarek
  */
class PhoneService
{
private:
    PhoneModel *model;

    /**
      * Szuka telefonu od id idPhone w wektorze vector
      * @return index w wektorze znalezionego telefonu, lub -1 gdy nie znaleziono
      */
    int searchPhone(int idPhone, QVector<Phone> vector);

public:
    PhoneService();
    ~PhoneService();

    QVector<Phone> getPhones(int contractorId);
    void addPhones(int contractor, QVector<Phone> phones);
    void editPhones(int contractor, QVector<Phone> phones);
    void removePhones(int contractor);

};

#endif // PHONESERVICE_H
