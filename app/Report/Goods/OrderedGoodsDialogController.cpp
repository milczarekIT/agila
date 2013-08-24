#include "OrderedGoodsDialogController.h"

OrderedGoodsDialogController::OrderedGoodsDialogController(QWidget *parent, QString type)
{
    tvModel = new OrderedGoodsTVModel(type);
    view = new OrderedGoodsDialogView(parent, this);

    if(type == "ZK")
        view->setWindowTitle("Towary zamówione przez klientów");
    else if(type == "ZD")
        view->setWindowTitle("Towary zamówione u dostawców");

    tvModel->getData();
    view->setTVModel(tvModel);

    restoreTableState();
}

OrderedGoodsDialogController::~OrderedGoodsDialogController()
{
    saveTableState();
}

void OrderedGoodsDialogController::exec()
{
    view->exec();
}

void OrderedGoodsDialogController::saveReport()
{
    ReportDataReader *reportDataReader = new ReportDataReader(view->getTableView());
    if(type == "ZK")
        doSaveReport(reportDataReader, view->windowTitle(), Report::ORDERED_CONTRACTOR_GOODS);
    else
        doSaveReport(reportDataReader, view->windowTitle(), Report::ORDERED_SUPPLIER_GOODS);
    view->accept();
}

void OrderedGoodsDialogController::restoreTableState() {
    tableStateManager = new TableStateManager();
    QByteArray state = tableStateManager->getState("REPORT_ORDERED_GOODS");
    view->getTableView()->horizontalHeader()->restoreState(state);

    delete tableStateManager;
}

void OrderedGoodsDialogController::saveTableState() {
    tableStateManager = new TableStateManager();
    QByteArray state = view->getTableView()->horizontalHeader()->saveState();
    QByteArray oldState = tableStateManager->getState("REPORT_ORDERED_GOODS");
    if(state != oldState)
        tableStateManager->saveState("REPORT_ORDERED_GOODS", state);

    delete tableStateManager;
}

