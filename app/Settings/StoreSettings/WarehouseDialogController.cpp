#include "WarehouseDialogController.h"

WarehouseDialogController::WarehouseDialogController(QWidget *parent)
{
    this->view = new WarehouseDialogView(this, parent);
    warehouseService = new WarehouseService();
    edit = false;
}

WarehouseDialogController::~WarehouseDialogController() {
    delete warehouseService;
}

void WarehouseDialogController::exec() {
    view->setWindowTitle("Dodaj nowy magazyn");

    if(view->exec()) {
        warehouse.setName(view->getLineName()->text());
        warehouse.setShortName(view->getLineShortName()->text());
        warehouse.setDefaultWarehouse(view->getCheckBoxDefault()->isChecked());

        int newWarehouseId = warehouseService->addWarehouse(warehouse);
        int importFromWarehouse = view->getButtonsImportWarehouse()->checkedId();

        warehouseService->importGoodsFromWarehouse(importFromWarehouse, newWarehouseId);
    }
}

void WarehouseDialogController::exec(int id) {
    edit = true;
    view->setWindowTitle("Edytuj magazyn");
    warehouse = warehouseService->getWarehouse(id);
    view->getLineName()->setText(warehouse.getName());
    view->getLineShortName()->setText(warehouse.getShortName());
    view->getCheckBoxDefault()->setChecked(warehouse.isDefaultWarehouse());
    view->getGroupBox()->hide();

    if(view->exec()) {
        warehouse.setName(view->getLineName()->text());
        warehouse.setShortName(view->getLineShortName()->text());
        warehouse.setDefaultWarehouse(view->getCheckBoxDefault()->isChecked());

        warehouseService->editWarehouse(warehouse);
    }

}

void WarehouseDialogController::suggestShortName(QString name) {
    view->getLineShortName()->setText(name.toUpper());
}

void WarehouseDialogController::checkIfAvailableName(QString name) {
    if(name != warehouse.getName()) // jeśli to nazwa tego magazynu to nie ma potrzeby sprawdzania
    {
        if(warehouseService->isNameAvailable(name))
            view->getLineNameNotAvailable()->setVisible(false);
        else
            view->getLineNameNotAvailable()->setVisible(true);
    }

}

void WarehouseDialogController::checkIfAvailableShortName(QString shortName) {
    if(shortName != warehouse.getShortName()) // jeśli to nazwa tego magazynu to nie ma potrzeby sprawdzania
    {
        if(warehouseService->isShortNameAvailable(shortName))
            view->getLineShortNameNotAvailable()->setVisible(false);
        else
            view->getLineShortNameNotAvailable()->setVisible(true);
    }
}
