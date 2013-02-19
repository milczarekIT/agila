#include "MissingGoodsDialogController.h"

MissingGoodsDialogController::MissingGoodsDialogController(QWidget *parent)
{
    view = new MissingGoodsDialogView(parent, this);
    tvModel = new ReportGoodsTVModel();

    tvModel->getData();
    view->setTVModel(tvModel);

    restoreTableState();
}

MissingGoodsDialogController::~MissingGoodsDialogController()
{
    saveTableState();
    delete tvModel;
}

void MissingGoodsDialogController::exec()
{
    view->exec();
}


void MissingGoodsDialogController::printReport()
{
   qDebug() << "Tu wstawić drukowanie rapotu: MissingGoodsDialogController::printReport()";
   view->accept();
}

void MissingGoodsDialogController::restoreTableState() {
    tableStateManager = new TableStateManager();
    QByteArray state = tableStateManager->getState("REPORT_MISSING_GOODS");
    view->getTableView()->horizontalHeader()->restoreState(state);

    delete tableStateManager;
}

void MissingGoodsDialogController::saveTableState() {
    tableStateManager = new TableStateManager();
    QByteArray state = view->getTableView()->horizontalHeader()->saveState();
    QByteArray oldState = tableStateManager->getState("REPORT_MISSING_GOODS");
    if(state != oldState)
        tableStateManager->saveState("REPORT_MISSING_GOODS", state);

    delete tableStateManager;
}
