#include "Tax.h"

Tax::Tax()
{

}

void Tax::setValue(float value)
{
    this->value = value;
}

void Tax::setShortName(QString shortName)
{
    this->shortName = shortName;
}

void Tax::setActiveInApp(bool activeInApp)
{
    this->activeInApp = activeInApp;
}

float Tax::getValue()
{
    return value;
}

QString Tax::getShortName()
{
    return shortName;
}

bool Tax::isActiveInApp()
{
    return activeInApp;
}

int Tax::operator ==(Tax t)
{
    if(this->id != t.getId())
        return 0;
    else if(this->name != t.getName())
        return 0;
    else if(this->value != t.getValue())
        return 0;
    else if(!(this->shortName == t.getShortName()))
        return 0;
    else if(this->activeInApp != t.isActiveInApp())
        return 0;
    else
        return 1;
}

