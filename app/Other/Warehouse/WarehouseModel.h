#ifndef WAREHOUSEMODEL_H
#define WAREHOUSEMODEL_H

#include "Database/Model.h"
#include "Other/Warehouse/Warehouse.h"

class WarehouseModel : public Model
{
public:
    WarehouseModel();

    QVector<Warehouse> getWarehouses();
    Warehouse getWarehouse(int id);
    int addWarehouse(Warehouse warehouse);
    void editWarehouse(Warehouse warehouse); // edycja nazwy magazynu
    void removeWarehouse(int id);

    bool isNameAvailable(QString name);
    bool isShortNameAvailable(QString shortName);

    /**
      * Ustawia domyślny magazyn o podanym id: deaktywuje poprzedni magazyn domyślny (jako nie-domyślny)
      */
    void setDefaultWarehouse(int id);
    Warehouse* getDefaultWarehouse();

    void importGoodsFromWarehouse(int fromWarehouse, int toWarehouse);

    // used in service
    bool isDefaultMagazineInDb();
    void setDefaultRandomWarehouseOtherThan(int warehouseId);

};

#endif // WAREHOUSEMODEL_H
