#include "InvoiceService.h"

InvoiceService::InvoiceService()
{
    model = new InvoiceModel();
    storeResultService->setDecreasedQuantity();
}

InvoiceService::~InvoiceService()
{
    delete model;
}

Invoice InvoiceService::getInvoice(QString symbol) {
    try {
        invoice = model->getInvoice(symbol);

        invoice.setRelatedDocuments(relatedDocumentModel->getRelatedDocuments(symbol));

        invoice.setDocumentPositions(documentPositionService->getPositions(symbol));
    } catch(SQLException *e) {
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }

    return invoice;
}

void InvoiceService::addInvoice(Invoice invoice) {
    try {
        Database::getInstance().db.transaction();

        model->addInvoice(invoice);

        documentPositionService->setStoreResult(invoice.getStoreResult());
        documentPositionService->addPositions(invoice.getSymbol(), invoice.getDocumentPositions());

        Database::getInstance().db.commit();
    } catch(SQLException *e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
}

void InvoiceService::editInvoice(Invoice newInvoice) {
    try {
        Database::getInstance().db.transaction();

        Invoice oldInvoice = this->getInvoice(invoice.getSymbol());
        model->editInvoice(newInvoice);

        documentPositionService->setStoreResult(newInvoice.getStoreResult());
        documentPositionService->updateDocumentPositions(oldInvoice, newInvoice);

        Database::getInstance().db.commit();
    } catch(SQLException *e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
}

void InvoiceService::removeInvoice(QString symbol, bool cancelStoreResult) {
    try {
        Database::getInstance().db.transaction();

        model->removeInvoice(symbol);
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
