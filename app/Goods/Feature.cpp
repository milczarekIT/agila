#include "Feature.h"

Feature::Feature()
{
}

Feature::Feature(int id, QString name)
{
    this->id = id;
    this->name = name;
}

void Feature::setId(int id)
{
    this->id = id;
}

void Feature::setName(QString name)
{
    this->name = name;
}

void Feature::setValue(QString value)
{
    this->value = value;
}

int Feature::getId()
{
    return id;
}

QString Feature::getName()
{
    return name;
}

QString Feature::getValue()
{
    return value;
}

int Feature::operator==(Feature f)
{
    if(this->id != f.getId())
        return 0;
    else if(this->name != f.getName())
        return 0;
    else if(this->value != f.getValue())
        return 0;
    else
        return 1;
}
