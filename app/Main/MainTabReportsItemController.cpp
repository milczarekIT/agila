#include "MainTabReportsItemController.h"

MainTabReportsItemController::MainTabReportsItemController(QWidget *parent)
{
    view = new MainTabReportsItem(this, parent);
}

MainTabItem *MainTabReportsItemController::getView()
{
    return view;
}

void MainTabReportsItemController::initModel()
{

}

void MainTabReportsItemController::dialogCurrentInvetory()
{
    CurrentInventoryDialogController *controller = new CurrentInventoryDialogController(this);
    controller->exec();
    delete controller;
}

void MainTabReportsItemController::dialogCurrentInvetoryGroups()
{
    CurrentInventoryGroupsDialogController *controller = new CurrentInventoryGroupsDialogController(this);
    controller->exec();
    delete controller;
}

void MainTabReportsItemController::dialogUnpaidSaleDocuments()
{
    UnpaidSaleDocumentDialogController *controller = new UnpaidSaleDocumentDialogController(this);
    controller->exec();
    delete controller;
}

void MainTabReportsItemController::dialogUnpaidPurchaseDocuments()
{
    UnpaidPurchaseDocumentDialogController *controller = new UnpaidPurchaseDocumentDialogController(this);
    controller->exec();
    delete controller;
}

void MainTabReportsItemController::dialogUnrealizedDocumentsZK()
{
    UnrealizedOrderDialogController *controller = new UnrealizedOrderDialogController(this, "ZK");
    controller->exec();
    delete controller;
}

void MainTabReportsItemController::dialogUnrealizedDocumentsZD()
{
    UnrealizedOrderDialogController *controller = new UnrealizedOrderDialogController(this, "ZD");
    controller->exec();
    delete controller;
}

void MainTabReportsItemController::dialogMissingGoods()
{
    MissingGoodsDialogController *controller = new MissingGoodsDialogController(this);
    controller->exec();
    delete controller;
}

void MainTabReportsItemController::dialogEndingGoods()
{
    EndingGoodsDialogController *controller = new EndingGoodsDialogController(this);
    controller->exec();
    delete controller;
}

void MainTabReportsItemController::dialogOrderedGoodsZK()
{
    OrderedGoodsDialogController *controller = new OrderedGoodsDialogController(this, "ZK");
    controller->exec();
    delete controller;
}

void MainTabReportsItemController::dialogOrderedGoodsZD()
{
    OrderedGoodsDialogController *controller = new OrderedGoodsDialogController(this, "ZD");
    controller->exec();
    delete controller;
}

void MainTabReportsItemController::dialogTopGoods()
{
    TopGoodsDialogController *controller = new TopGoodsDialogController(this);
    controller->exec();
    delete controller;
}

void MainTabReportsItemController::dialogTopContractors()
{
    TopContractorsDialogController *controller = new TopContractorsDialogController(this);
    controller->exec();
    delete controller;
}

ModuleManager::Module MainTabReportsItemController::module()
{
    return ModuleManager::Reports;
}
