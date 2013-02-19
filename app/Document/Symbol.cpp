#include "Symbol.h"

Symbol::Symbol()
{
    nr = 0;
    dd = 0;
    mm = 0;
    yyyy = 0;
}


void Symbol::setNr(int nr)
{
    this->nr = nr;
}

void Symbol::setDay(int dd)
{
    this->dd = dd;
}

void Symbol::setMonth(int mm)
{
    this->mm =mm;
}

void Symbol::setYear(int yyyy)
{
    this->yyyy = yyyy;
}

int Symbol::getNr()
{
    return nr;
}

int Symbol::getDay()
{
    return dd;
}

int Symbol::getMonth()
{
    return mm;
}

int Symbol::getYear()
{
    return yyyy;
}
