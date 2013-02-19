#ifndef UNITMODEL_H
#define UNITMODEL_H

#include "Database/Model.h"
#include "Goods/Unit.h"

class UnitModel : public Model
{
public:
    UnitModel();
    ~UnitModel();

    QVector<Unit> getUnits();
    Unit getUnit(int id);
    void addUnit(Unit u);
    void editUnit(Unit u);
    void removeUnit(int id);
};

#endif // UNITMODEL_H
