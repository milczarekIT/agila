#include "UnpaidSaleDocumentDialogController.h"

UnpaidSaleDocumentDialogController::UnpaidSaleDocumentDialogController(QWidget *parent) : UnpaidDocumentDialogController(parent)
{
    tvModel->getUnpaidSaleDocuments();
    view->initTVColumnWidhts();

    view->getLineValue()->setText(tvModel->getUnpaidSaleValue().toString());

    view->setWindowTitle("Niezapłacone dokumenty sprzedaży");

    restoreTableState();
}


UnpaidSaleDocumentDialogController::~UnpaidSaleDocumentDialogController() {
    saveTableState();
}

void UnpaidSaleDocumentDialogController::saveReport()
{
    ReportDataReader *reportDataReader = new ReportDataReader(view->getTableView());
    doSaveReport(reportDataReader, view->windowTitle(),  Report::UNPAID_SALE_DOCUMENTS);
    view->accept();
}

void UnpaidSaleDocumentDialogController::showOnlyNotPaidOnTime(bool checked)
{
    this->initNotPaidOnTimeFilterInModel(checked);
    tvModel->getUnpaidSaleDocuments();

    view->getLineValue()->setText(tvModel->getUnpaidSaleValue().toString());
}

