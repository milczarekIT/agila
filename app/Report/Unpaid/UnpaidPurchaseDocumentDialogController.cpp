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

void UnpaidPurchaseDocumentDialogController::printReport()
{
    qDebug() << "Tu wstawić drukowanie rapotu: UnpaidPurchaseDocumentDialogController::printReport()";
    view->accept();
}

void UnpaidPurchaseDocumentDialogController::showOnlyNotPaidOnTime(bool checked)
{
    this->initNotPaidOnTimeFilterInModel(checked);
    tvModel->getUnpaidPurchaseDocuments();

    view->getLineValue()->setText(tvModel->getUnpaidPurchaseDocumentsValue().toString());
}
