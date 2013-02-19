#ifndef WAREHOUSESERVICE_H
#define WAREHOUSESERVICE_H

#include "Other/Service.h"
#include "Other/Warehouse/WarehouseModel.h"

class WarehouseService : public Service
{
    WarehouseModel *model;
public:
    WarehouseService();
    ~WarehouseService();

    QVector<Warehouse> getWarehouses();
    Warehouse getWarehouse(int id);
    int addWarehouse(Warehouse warehouse);
    void editWarehouse(Warehouse warehouse);
    void removeWarehouse(int id);

    void importGoodsFromWarehouse(int fromWarehouse, int toWarehouse);

    bool isNameAvailable(QString name);
    bool isShortNameAvailable(QString shortName);

    void setDefaultWarehouse(int id);
    Warehouse* getDefaultWarehouse();
};

#endif // WAREHOUSESERVICE_H
