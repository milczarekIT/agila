#include "DocumentFKService.h"

DocumentFKService::DocumentFKService()
{
    model = new DocumentFKModel();
    storeResultService->setDecreasedQuantity();
    documentPositionFKService = new DocumentPositionFKService(storeResultService);
}

DocumentFKService::~DocumentFKService()
{
    delete model;
    delete documentPositionFKService;
}

DocumentFK DocumentFKService::getDocumentFK(QString symbol) {
    try {
        InvoiceService *invoiceService = new InvoiceService();
        QString invoiceSymbol;

        documentFK = model->getDocumentFK(symbol);
        invoiceSymbol = model->getInvoiceSymbolByDocumentFK(symbol);
        documentFK.setInvoice(invoiceService->getInvoice(invoiceSymbol));

        documentFK.setDocumentPositions(documentPositionService->getPositions(symbol));
        documentFK.setRelatedDocuments(relatedDocumentModel->getRelatedDocuments(symbol));

        delete invoiceService;
    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }

   return documentFK;
}

void DocumentFKService::addDocumentFK(DocumentFK fk) {
    try {
        Database::getInstance().db.transaction();

        model->addDocumentFK(fk);

        relatedDocumentModel->addLinkToDocument(fk.getInvoice().getSymbol(), fk.getSymbol());
        documentPositionFKService->addPositions(fk.getSymbol(), fk.getDocumentPositions(), fk.getInvoice().getDocumentPositions());

        Database::getInstance().db.commit();
    } catch(SQLException *e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
}

void DocumentFKService::editDocumentFK(DocumentFK newFk) {
    try {
        Database::getInstance().db.transaction();

        model->editDocumentFK(newFk);
        DocumentFK oldFk = this->getDocumentFK(newFk.getSymbol());

        documentPositionFKService->setStoreResult(newFk.getStoreResult());
        documentPositionFKService->updateDocumentPositions(oldFk, newFk);

        relatedDocumentModel->editLinkToBaseDocument(newFk.getInvoice().getSymbol(), newFk.getSymbol());

        Database::getInstance().db.commit();
    } catch(SQLException *e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
}

void DocumentFKService::removeDocumentFK(QString symbol, bool cancelStoreResult) {
    try {
        Database::getInstance().db.transaction();

        model->removeDocumentFK(symbol);

        if(cancelStoreResult)
        {
            documentFK = this->getDocumentFK(symbol);
            documentPositionFKService->cancelDiffStoreResultForPositions(documentFK.getDocumentPositions(), documentFK.getInvoice().getDocumentPositions());
        }

        documentPositionService->removePositions(symbol);
        relatedDocumentModel->removeLinksToDocument(symbol);

        Database::getInstance().db.commit();
    } catch(SQLException *e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
}
