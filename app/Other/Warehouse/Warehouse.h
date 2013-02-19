#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <QString>
#include "Other/SimpleStructure.h"

class Warehouse : public SimpleStructure
{
    QString shortName;
    bool defaultWarehouse;
public:
    Warehouse();

    void setShortName(QString shortName);
    void setDefaultWarehouse(bool defaultWarehouse);

    QString getShortName();
    bool isDefaultWarehouse();

};

#endif // WAREHOUSE_H
