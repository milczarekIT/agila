#ifndef PHONE_H
#define PHONE_H

#include <QString>
#include "Other/SimpleStructure.h"

class Phone : public SimpleStructure
{
private:
    QString number;
    bool defaultPhone;
public:
    Phone();
    Phone (QString name, QString number, bool defaultPhone);
    Phone (int id, QString name, QString number, bool defaultPhone);

    void setNumber (QString postcode);
    void setDefault(bool defaultPhone);

    QString getNumber ();
    bool isDefault();

    int operator==(Phone p);
};

#endif // PHONE_H
