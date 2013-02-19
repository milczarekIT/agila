#include "SettingsMagazineItemController.h"

SettingsMagazineItemController::SettingsMagazineItemController(WarehouseService *service,Warehouse warehouse, QWidget *parent) :
    QFrame(parent)
{
    messageBox = new MessageBox(parent);
    this->view = new SettingsMagazineItemView(service,warehouse,this,parent);
}

SettingsMagazineItemView * SettingsMagazineItemController::getView()
{
    return view;
}

void SettingsMagazineItemController::emitEditSignal()
{
    int warehouseId = view->getWarehouse().getId();
    emit editButtonClicked(warehouseId);
}

void SettingsMagazineItemController::emitDeleteSignal()
{
    int warehouseId = view->getWarehouse().getId();
    emit removeButtonClicked(warehouseId);
}

