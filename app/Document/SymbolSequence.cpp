#include "SymbolSequence.h"

SymbolSequence::SymbolSequence()
{

}

SymbolSequence::SymbolSequence(QString sequence, int index)
{
    this->sequence = sequence;
    this->index = index;
}

void SymbolSequence::setSequence(QString sequence)
{
    this->sequence = sequence;
}

void SymbolSequence::setIndex(int index)
{
    this->index = index;
}

QString SymbolSequence::getSequence()
{
    return sequence;
}

int SymbolSequence::getIndex()
{
    return index;
}
