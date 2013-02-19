#include "MainStoreComboBoxController.h"

MainStoreComboBoxController::MainStoreComboBoxController()
{
    this->view = new MainStoreComboBox(this);
    warehouseService = new WarehouseService();
    setDataIntoStoreComboBox();
    setCurrentStoreInStoreComboBox();
}

MainStoreComboBoxController::~MainStoreComboBoxController()
{
    delete warehouseService;
}

MainStoreComboBox *MainStoreComboBoxController::getView()
{
    return view;
}

void MainStoreComboBoxController::setDataIntoStoreComboBox()
{
    view->clear();
    QVector<Warehouse> warehouses = warehouseService->getWarehouses();
    for(int i = 0; i < warehouses.size(); i++)
        view->addItem(warehouses[i].getName(), warehouses[i].getId());
}

void MainStoreComboBoxController::setCurrentStoreInStoreComboBox()
{
    Warehouse *defaultWarehouse = warehouseService->getDefaultWarehouse();
    ApplicationManager::getInstance()->setWarehouse(*defaultWarehouse);

    int currentIndex = view->findData(QVariant(defaultWarehouse->getId()));
    view->setCurrentIndex(currentIndex);
}

void MainStoreComboBoxController::switchStore(int index)
{
    if (index > -1)
    {
        int id = view->itemData(index).toInt();
        ApplicationManager::getInstance()->setWarehouse(warehouseService->getWarehouse(id));

        emit storeSwitched();
    }
}
