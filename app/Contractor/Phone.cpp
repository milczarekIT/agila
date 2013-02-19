#include "Phone.h"

Phone::Phone()
{

}

Phone::Phone (QString name, QString number, bool defaultPhone)
{
    id = 0;
    this->name = name;
    this->number = number;
    this->defaultPhone = defaultPhone;
}

Phone::Phone (int id, QString name, QString number, bool defaultPhone)
{
    this->id = id;
    this->name = name;
    this->number = number;
    this->defaultPhone = defaultPhone;
}

void Phone::setNumber (QString number)
{
    this->number=number;
}

void Phone::setDefault(bool defaultPhone)
{
    this->defaultPhone = defaultPhone;
}

QString Phone::getNumber ()
{
    return number;
}

bool Phone::isDefault()
{
    return defaultPhone;
}

int Phone::operator==(Phone p)
{
    if(this->id != p.getId())
        return 0;
    else if(this->name != p.getName())
        return 0;
    else if(this->number != p.getNumber())
        return 0;
    else if(this->defaultPhone != p.isDefault())
        return 0;
    else
        return 1;
}

