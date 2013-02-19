#include "PurchaseController.h"

PurchaseController::PurchaseController()
{
}

PurchaseController::~PurchaseController(){}

bool PurchaseController::isChangesOccured() {
    return !(manager->getPurchasePolicy()->getPurchaseInvoiceOld() == manager->getPurchasePolicy()->getPurchaseInvoice());
}

void PurchaseController::changedPaid()
{
 if(view->getPaymentDate()->date()<=view->getDateIssue())
    view->setCheckPaid(true);
 else
    view->setCheckPaid(false);
}
void  PurchaseController:: fillBox(QComboBox *box,QVector<MethodOfPayment> values)
{
    for(int i = 0; i < values.size(); i++)
        box->addItem(values[i].getName(), QVariant::fromValue(values[i].getId()));
}

void PurchaseController::updatePaymentDate()
{   view->getPaymentDate()->setDate(QDate::currentDate().addDays(
    mopModel->getMethodOfPayment(view->getWayToPay()->itemData(view->getWayToPay()->currentIndex()).toInt()).getMaturity()));
}

void PurchaseController::printDoc()
{
        PrintPurchaseDocumentController *pc = new PrintPurchaseDocumentController(view->getLineDocumentSymbol()->text());
        PurchaseInvoice doc = purchaseInvoiceService->getPurchaseInvoice(view->getLineDocumentSymbol()->text());
        pc->print(&doc);
        delete pc;
}
