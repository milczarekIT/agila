#include "PurchaseInvoiceService.h"

PurchaseInvoiceService::PurchaseInvoiceService()
{
    model = new PurchaseInvoiceModel();
    storeResultService->setIncreasedQuantity();
}

PurchaseInvoiceService::~PurchaseInvoiceService() {
    delete model;
}

PurchaseInvoice PurchaseInvoiceService::getPurchaseInvoice(QString symbol) {
    try {
        invoice = model->getPurchaseInvoice(symbol);

        invoice.setRelatedDocuments(relatedDocumentModel->getRelatedDocuments(symbol));

        invoice.setDocumentPositions(documentPositionService->getPositions(symbol));
    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }

    return invoice;
}

void PurchaseInvoiceService::addPurchaseInvoice(PurchaseInvoice invoice) {
    try {
        Database::getInstance().db.transaction();

        model->addPurchaseInvoice(invoice);

        documentPositionService->setStoreResult(invoice.getStoreResult());
        documentPositionService->addPositions(invoice.getSymbol(), invoice.getDocumentPositions());

        Database::getInstance().db.commit();
    } catch(SQLException *e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
}

void PurchaseInvoiceService::editPurchaseInvoice(PurchaseInvoice newInvoice) {
    try {
        Database::getInstance().db.transaction();

        PurchaseInvoice oldInvoice = this->getPurchaseInvoice(invoice.getSymbol());
        model->editPurchaseInvoice(newInvoice);

        documentPositionService->setStoreResult(newInvoice.getStoreResult());
        documentPositionService->updateDocumentPositions(oldInvoice, newInvoice);

        Database::getInstance().db.commit();
    } catch(SQLException *e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
}

void PurchaseInvoiceService::removePurchaseInvoice(QString symbol, bool cancelStoreResult) {
    try {
        Database::getInstance().db.transaction();

        model->removePurchaseInvoice(symbol);
        if(cancelStoreResult)
            storeResultService->cancelStoreResult(getPositions(symbol));

        documentPositionService->removePositions(symbol);
        relatedDocumentModel->removeLinksToDocument(symbol);

        Database::getInstance().db.commit();
    } catch(SQLException *e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
}
