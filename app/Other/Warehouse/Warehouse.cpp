#include "Warehouse.h"

Warehouse::Warehouse()
{
    defaultWarehouse = false;
    shortName = "";
}

void Warehouse::setShortName(QString shortName) { this->shortName = shortName; }
void Warehouse::setDefaultWarehouse(bool defaultWarehouse) { this->defaultWarehouse = defaultWarehouse; }

QString Warehouse::getShortName() { return shortName; }
bool Warehouse::isDefaultWarehouse() { return defaultWarehouse; }




