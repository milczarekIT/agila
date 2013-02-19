#include "SimpleStructure.h"


SimpleStructure::SimpleStructure()
{
    this->id = 0;
    this->name = "";
}

SimpleStructure::SimpleStructure(int id, QString name)
{
    this->id = id;
    this->name = name;
}

void SimpleStructure::setId(int id)
{
    this->id = id;
}

void SimpleStructure::setName(QString name)
{
    this->name = name;
}

int SimpleStructure::getId()
{
    return id;
}

QString SimpleStructure::getName()
{
    return name;
}

int SimpleStructure::operator ==(SimpleStructure ss)
{
    if(this->id != ss.getId())
        return 0;
    else if(this->name != ss.getName())
        return 0;
    else
        return 1;
}
