#include "SourceOfMember.h"

QString SourceOfMember::toString()
{
    return QString("--Źródło pozyskania - id: ") + QVariant(this->id).toString() + QString(", Nazwa .: ")  + this->name + QString(" --,");
}

int SourceOfMember::operator ==(SourceOfMember som)
{
    if(this->id != som.getId())
        return 0;
    else if(this->name != som.getName())
        return 0;
    else
        return 1;
}
