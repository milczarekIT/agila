#ifndef CONTRACTORADDITIONALID_H
#define CONTRACTORADDITIONALID_H

#include <QDebug>
#include "Other/SimpleStructure.h"

/**
  * Dodatkowy identyfikator kontrahenta np. NIP, PESEL, REGON etc
  * Typ to SimpleStructure czyli nazwa i id z bazy (nazwa: NIP)
  * Wartość to zawartość wybranego typu np. 834-100-80-40
  * @author Bartosz Milczarek
  */
class ContractorAdditionalId
{
    SimpleStructure type;
    QString value;
public:
    ContractorAdditionalId();

    void setType(SimpleStructure type);
    void setValue(QString value);

    SimpleStructure getType();
    QString getValue();

    int operator ==(ContractorAdditionalId cg);

};

#endif // CONTRACTORADDITIONALID_H
