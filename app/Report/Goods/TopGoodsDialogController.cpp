#include "TopGoodsDialogController.h"

TopGoodsDialogController::TopGoodsDialogController(QWidget *parent)
{
    view = new TopGoodsDialogView(parent, this);

    tvModel = new TopGoodsTVModel();

    tvModel->getData();
    view->setTVModel(tvModel);

    initModelFromInterfaceData();
    restoreTableState();
}

TopGoodsDialogController::~TopGoodsDialogController()
{
    saveTableState();
}

void TopGoodsDialogController::initModelFromInterfaceData()
{
    this->setListLimitFilter(view->getSpinBoxListLimit()->value());
    this->setDateFromFilter(view->getDateEditFrom()->date());
    this->setDateToFilter(view->getDateEditTo()->date());
}

void TopGoodsDialogController::exec()
{
    view->exec();
}

void TopGoodsDialogController::printReport()
{
   qDebug() << "Tu wstawić drukowanie rapotu: TopGoodsDialogController::printReport()";
   view->accept();
}

void TopGoodsDialogController::setListLimitFilter(int limit)
{
    tvModel->setListLimitFilter(limit);
    tvModel->getData();
}

void TopGoodsDialogController::setDateFromFilter(QDate fromDate)
{
    tvModel->setDateFromFilter(fromDate);
    tvModel->getData();
}

void TopGoodsDialogController::setDateToFilter(QDate toDate)
{
    tvModel->setDateToFilter(toDate);
    tvModel->getData();
}

void TopGoodsDialogController::restoreTableState() {
    tableStateManager = new TableStateManager();
    QByteArray state = tableStateManager->getState("REPORT_TOP_GOODS");
    view->getTableView()->horizontalHeader()->restoreState(state);

    delete tableStateManager;
}

void TopGoodsDialogController::saveTableState() {
    tableStateManager = new TableStateManager();
    QByteArray state = view->getTableView()->horizontalHeader()->saveState();
    QByteArray oldState = tableStateManager->getState("REPORT_TOP_GOODS");
    if(state != oldState)
        tableStateManager->saveState("REPORT_TOP_GOODS", state);

    delete tableStateManager;
}
