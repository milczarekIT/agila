#include "SettingsMagazineController.h"

SettingsMagazineController::SettingsMagazineController(QWidget *parent) :
    QWidget(parent)
{
    messageBox = new MessageBox(parent);
    warehouseService = new WarehouseService();
    this->view = new SettingsMagazineView(this,parent);
}

SettingsMagazineController::~SettingsMagazineController() {
    delete warehouseService;
}

SettingsMagazineView * SettingsMagazineController::getView()
{
    return view;
}

void SettingsMagazineController::addWarehouse()
{
    WarehouseDialogController *warehouseDialog = new WarehouseDialogController();
    warehouseDialog->exec();
    delete warehouseDialog;

    view->deleteWidgets();
    emit warehouseChanged();
}

void SettingsMagazineController::editWarehouse(int id)
{
    WarehouseDialogController *warehouseDialog = new WarehouseDialogController();
    warehouseDialog->exec(id);
    delete warehouseDialog;

    view->deleteWidgets();
    emit warehouseChanged();
}

void SettingsMagazineController::removeWarehouse(int id)
{
    if (messageBox->createQuestionBox("      Usuwanie magazynu !         ") == MessageBox::YES)
    {
        warehouseService->removeWarehouse(id);
        view->deleteWidgets();
    }
}


void SettingsMagazineController::emitMagazineChanged()
{
    emit warehouseChanged();
}
