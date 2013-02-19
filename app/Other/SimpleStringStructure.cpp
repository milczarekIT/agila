#include "SimpleStringStructure.h"

SimpleStringStructure::SimpleStringStructure()
{
    id = "";
    name = "";
}

void SimpleStringStructure::setId(QString id) {
    this->id = id;
}

void SimpleStringStructure::setName(QString name) {
    this->name = name;
}

QString SimpleStringStructure::getId() {
    return id;
}

QString SimpleStringStructure::getName() {
    return name;
}
