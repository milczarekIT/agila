#ifndef PEOPLEMODEL_H
#define PEOPLEMODEL_H

#include "Database/Model.h"

class PeopleModel : public Model
{
    int addPerson(QString name);
public:
    PeopleModel();
    ~PeopleModel();

    /**
      * Pobiera id osoby (wystawiającej/odbierajacej dokument)
      * Jeśli nie ma tej osoby w bazie, to dodaje do bazy i zwraca nowododany id
      */
    int getPersonId(QString name);
    QString getName(int id);
};

#endif // PEOPLEMODEL_H
