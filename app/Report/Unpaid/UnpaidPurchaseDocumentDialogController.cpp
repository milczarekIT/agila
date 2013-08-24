#include "UnpaidPurchaseDocumentDialogController.h"

UnpaidPurchaseDocumentDialogController::UnpaidPurchaseDocumentDialogController(QWidget *parent) : UnpaidDocumentDialogController(parent)
{
    tvModel->getUnpaidPurchaseDocuments();
    view->initTVColumnWidhts();

    view->getLineValue()->setText(tvModel->getUnpaidPurchaseDocumentsValue().toString());

    view->setWindowTitle("Niezapłacone dokumenty zakupu");

    restoreTableState();
}

UnpaidPurchaseDocumentDialogController::~UnpaidPurchaseDocumentDialogController()
{
    saveTableState();
}

void UnpaidPurchaseDocumentDialogController::saveReport()
{
    ReportDataReader *reportDataReader = new ReportDataReader(view->getTableView());
    doSaveReport(reportDataReader, view->windowTitle(),  Report::UNPAID_PURCHASE_DOCUMENTS);
    view->accept();
}

void UnpaidPurchaseDocumentDialogController::showOnlyNotPaidOnTime(bool checked)
{
    this->initNotPaidOnTimeFilterInModel(checked);
    tvModel->getUnpaidPurchaseDocuments();

    view->getLineValue()->setText(tvModel->getUnpaidPurchaseDocumentsValue().toString());
}
