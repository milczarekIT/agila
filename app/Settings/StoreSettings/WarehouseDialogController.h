#ifndef WAREHOUSEDIALOGCONTROLLER_H
#define WAREHOUSEDIALOGCONTROLLER_H

#include <QWidget>
#include "Settings/StoreSettings/WarehouseDialogView.h"
#include "Other/Warehouse/Warehouse.h"
#include "Other/Warehouse/WarehouseService.h"
class WarehouseDialogView;

class WarehouseDialogController : public QWidget
{
    Q_OBJECT
private:
    WarehouseDialogView *view;
    WarehouseService *warehouseService;
    Warehouse warehouse;

    bool edit;
public:
    WarehouseDialogController(QWidget *parent = 0);
    ~WarehouseDialogController();

    void exec();
    void exec(int id);

public slots:
    void suggestShortName(QString name);
    void checkIfAvailableName(QString name);
    void checkIfAvailableShortName(QString shortName);
};

#endif // WAREHOUSEDIALOGCONTROLLER_H
