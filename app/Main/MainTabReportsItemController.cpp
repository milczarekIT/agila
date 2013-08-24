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

void MainTabReportsItemController::generateCurrentInventory()
{
    CurrentInventoryDialogController *controller = new CurrentInventoryDialogController(this);
    controller->exec();
    delete controller;
}

void MainTabReportsItemController::generateCurrentInventoryGroups()
{
    CurrentInventoryGroupsDialogController *controller = new CurrentInventoryGroupsDialogController(this);
    controller->exec();
    delete controller;
}

void MainTabReportsItemController::generateUnpaidSaleDocuments()
{
    UnpaidSaleDocumentDialogController *controller = new UnpaidSaleDocumentDialogController(this);
    controller->exec();
    delete controller;
}

void MainTabReportsItemController::generateUnpaidPurchaseDocuments()
{
    UnpaidPurchaseDocumentDialogController *controller = new UnpaidPurchaseDocumentDialogController(this);
    controller->exec();
    delete controller;
}

void MainTabReportsItemController::generateUnrealizedDocumentsZK()
{
    UnrealizedOrderDialogController *controller = new UnrealizedOrderDialogController(this, "ZK");
    controller->exec();
    delete controller;
}

void MainTabReportsItemController::generateUnrealizedDocumentsZD()
{
    UnrealizedOrderDialogController *controller = new UnrealizedOrderDialogController(this, "ZD");
    controller->exec();
    delete controller;
}

void MainTabReportsItemController::generateMissingGoods()
{
    MissingGoodsDialogController *controller = new MissingGoodsDialogController(this);
    controller->exec();
    delete controller;
}

void MainTabReportsItemController::generateEndingGoods()
{
    EndingGoodsDialogController *controller = new EndingGoodsDialogController(this);
    controller->exec();
    delete controller;
}

void MainTabReportsItemController::generateOrderedGoodsZK()
{
    OrderedGoodsDialogController *controller = new OrderedGoodsDialogController(this, "ZK");
    controller->exec();
    delete controller;
}

void MainTabReportsItemController::generateOrderedGoodsZD()
{
    OrderedGoodsDialogController *controller = new OrderedGoodsDialogController(this, "ZD");
    controller->exec();
    delete controller;
}

void MainTabReportsItemController::generateTopGoods()
{
    TopGoodsDialogController *controller = new TopGoodsDialogController(this);
    controller->exec();
    delete controller;
}

void MainTabReportsItemController::generateTopContractors()
{
    TopContractorsDialogController *controller = new TopContractorsDialogController(this);
    controller->exec();
    delete controller;
}

void MainTabReportsItemController::showCurrentInventory() {
    ReportListDialogController *controller = new ReportListDialogController(Report::CURRENT_INVENTORY, this);
    controller->exec();
    delete controller;
}

void MainTabReportsItemController::showCurrentInventoryGroups() {
    ReportListDialogController *controller = new ReportListDialogController(Report::CURRENT_INVENTORY_GROUP, this);
    controller->exec();
    delete controller;
}

void MainTabReportsItemController::showUnpaidSaleDocuments() {
    ReportListDialogController *controller = new ReportListDialogController(Report::UNPAID_SALE_DOCUMENTS, this);
    controller->exec();
    delete controller;
}

void MainTabReportsItemController::showUnpaidPurchaseDocuments() {
    ReportListDialogController *controller = new ReportListDialogController(Report::UNPAID_PURCHASE_DOCUMENTS, this);
    controller->exec();
    delete controller;
}

void MainTabReportsItemController::showUnrealizedDocumentsZK() {
    ReportListDialogController *controller = new ReportListDialogController(Report::UNREALIZED_ZK_ORDERS, this);
    controller->exec();
    delete controller;
}

void MainTabReportsItemController::showUnrealizedDocumentsZD() {
    ReportListDialogController *controller = new ReportListDialogController(Report::UNREALIZED_ZD_ORDERS, this);
    controller->exec();
    delete controller;
}

void MainTabReportsItemController::showMissingGoods() {
    ReportListDialogController *controller = new ReportListDialogController(Report::MISSING_GOODS, this);
    controller->exec();
    delete controller;
}

void MainTabReportsItemController::showEndingGoods() {
    ReportListDialogController *controller = new ReportListDialogController(Report::ENDING_GOODS, this);
    controller->exec();
    delete controller;
}

void MainTabReportsItemController::showOrderedGoodsZK() {
    ReportListDialogController *controller = new ReportListDialogController(Report::ORDERED_CONTRACTOR_GOODS, this);
    controller->exec();
    delete controller;
}

void MainTabReportsItemController::showOrderedGoodsZD() {
    ReportListDialogController *controller = new ReportListDialogController(Report::ORDERED_SUPPLIER_GOODS, this);
    controller->exec();
    delete controller;
}

void MainTabReportsItemController::showTopGoods() {
    ReportListDialogController *controller = new ReportListDialogController(Report::BESTSELLER_GOODS, this);
    controller->exec();
    delete controller;
}

void MainTabReportsItemController::showTopContractors() {
    ReportListDialogController *controller = new ReportListDialogController(Report::TOP_CONTRACTORS, this);
    controller->exec();
    delete controller;
}

ModuleManager::Module MainTabReportsItemController::module()
{
    return ModuleManager::Reports;
}

void MainTabReportsItemController::menuActionClicked(QAction* action) {
    QString actionName = action->property("actionName").toString();
    QString buttonName = action->property("buttonName").toString();


    QString firstLetter = buttonName.mid(0, 1).toUpper();
    QString restName = buttonName.mid(1);

    QString methodName = "";
    if(actionName == MainTabReportsItem::ACTION_MENU_GENERATE) {
        methodName = "generate" + firstLetter + restName;

    } else if(actionName == MainTabReportsItem::ACTION_MENU_SHOW) {
        methodName = "show" + firstLetter + restName;
    }

    if(methodName != "") {
        Reflection *reflection = new Reflection(this);
        if(reflection->containsMethod(methodName))
            reflection->invokeMethod(methodName);
        else
            qDebug() << "method " << methodName << " not found";

        reflection = NULL;
    }
}
