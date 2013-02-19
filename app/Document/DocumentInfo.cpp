#include "DocumentInfo.h"

DocumentInfo::DocumentInfo()
{
}

QString DocumentInfo::getType() {
    return this->type;
}

QString DocumentInfo::getName() {
    return name;
}

QString DocumentInfo::getNumbering() {
    return numbering;
}

QString DocumentInfo::getAfterText() {
    return afterText;
}

SimpleStringStructure DocumentInfo::getFamily() {
    return family;
}

void DocumentInfo::setType(QString type) {
    this->type = type;
}

void DocumentInfo::setName(QString name) {
    this->name = name;
}

void DocumentInfo::setNumbering(QString numbering) {
    this->numbering = numbering;
}

void DocumentInfo::setAfterText(QString afterText) {
    this->afterText = afterText;
}

void DocumentInfo::setFamily(SimpleStringStructure family) {
    this->family = family;
}
