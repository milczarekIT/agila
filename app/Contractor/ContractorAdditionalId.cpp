#include "ContractorAdditionalId.h"

ContractorAdditionalId::ContractorAdditionalId()
{
    this->value = "";
}

void ContractorAdditionalId::setType(SimpleStructure type) {
    this->type = type;
}

void ContractorAdditionalId::setValue(QString value) {
    this->value = value;
}

SimpleStructure ContractorAdditionalId::getType() {
    return type;
}

QString ContractorAdditionalId::getValue() {
    return value;
}

int ContractorAdditionalId::operator ==(ContractorAdditionalId additionalId)
{
    if(!(this->type == additionalId.getType()))
        return 0;
    else if(this->value != additionalId.getValue())
        return 0;
    else
        return 1;
}
