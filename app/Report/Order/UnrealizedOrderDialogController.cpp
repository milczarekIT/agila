#include "UnrealizedOrderDialogController.h"

UnrealizedOrderDialogController::UnrealizedOrderDialogController(QWidget *parent, QString type)
{
    this->type = type;
    view = new UnrealizedOrderDialogView(parent, this);

    if(type == "ZK")
        view->setWindowTitle("Niezrealizowane zamówienia od klientów");
    else if(type == "ZD")
        view->setWindowTitle("Niezrealizowane zamówienia do dostawców");

    tvModel = new UnrealizedOrderTVModel(type);

    tvModel->getData();
    view->setTVModel(tvModel);

    view->getLineValue()->setText(tvModel->getValue().toString());

    restoreTableState();
}

UnrealizedOrderDialogController::~UnrealizedOrderDialogController()
{
    saveTableState();
}

void UnrealizedOrderDialogController::exec()
{
   view->exec();
}

void UnrealizedOrderDialogController::printReport()
{
   qDebug() << "Tu wstawić drukowanie rapotu: UnrealizedOrderDialogController::printReport()";
   view->accept();
}

void UnrealizedOrderDialogController::restoreTableState() {
    tableStateManager = new TableStateManager();
    QByteArray state = tableStateManager->getState("REPORT_UNREALIZED_ORDERS");
    view->getTableView()->horizontalHeader()->restoreState(state);

    delete tableStateManager;
}

void UnrealizedOrderDialogController::saveTableState() {
    tableStateManager = new TableStateManager();
    QByteArray state = view->getTableView()->horizontalHeader()->saveState();
    QByteArray oldState = tableStateManager->getState("REPORT_UNREALIZED_ORDERS");
    if(state != oldState)
        tableStateManager->saveState("REPORT_UNREALIZED_ORDERS", state);

    delete tableStateManager;
}
