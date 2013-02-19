#include "DocumentFZKService.h"

DocumentFZKService::DocumentFZKService()
{
    model = new DocumentFZKModel();
    storeResultService->setIncreasedQuantity();
    documentPositionFKService = new DocumentPositionFKService(storeResultService);
}

DocumentFZKService::~DocumentFZKService()
{
    delete model;
    delete documentPositionFKService;
}

DocumentFZK DocumentFZKService::getDocumentFZK(QString symbol) {
    try {
        documentFZK = model->getDocumentFZK(symbol);
        documentFZK.setDocumentPositions(documentPositionService->getPositions(symbol));
        documentFZK.setRelatedDocuments(relatedDocumentModel->getRelatedDocuments(symbol));

    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }

   return documentFZK;
}

void DocumentFZKService::addDocumentFZK(DocumentFZK document) {
    try {
        Database::getInstance().db.transaction();

        model->addDocumentFZK(document);

        relatedDocumentModel->addLinkToDocument(document.getInvoice().getSymbol(), document.getSymbol());
        documentPositionFKService->addPositions(document.getSymbol(), document.getDocumentPositions(), document.getInvoice().getDocumentPositions());

        Database::getInstance().db.commit();
    } catch(SQLException *e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
}

void DocumentFZKService::editDocumentFZK(DocumentFZK newDocument) {
    try {
        Database::getInstance().db.transaction();

        model->editDocumentFZK(newDocument);
        DocumentFZK oldDocument = this->getDocumentFZK(newDocument.getSymbol());

        documentPositionFKService->setStoreResult(newDocument.getStoreResult());
        documentPositionFKService->updateDocumentPositions(oldDocument, newDocument);

        relatedDocumentModel->editLinkToBaseDocument(newDocument.getInvoice().getSymbol(), newDocument.getSymbol());

        Database::getInstance().db.commit();
    } catch(SQLException *e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
}

void DocumentFZKService::removeDocumentFZK(QString symbol, bool cancelStoreResult) {
    try {
        Database::getInstance().db.transaction();

        model->removeDocumentFZK(symbol);

        if(cancelStoreResult)
        {
            documentFZK = this->getDocumentFZK(symbol);
            documentPositionFKService->cancelDiffStoreResultForPositions(documentFZK.getDocumentPositions(), documentFZK.getInvoice().getDocumentPositions());
        }

        documentPositionService->removePositions(symbol);
        relatedDocumentModel->removeLinksToDocument(symbol);

        Database::getInstance().db.commit();
    } catch(SQLException *e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
}
