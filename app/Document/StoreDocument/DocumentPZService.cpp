#include "DocumentPZService.h"

DocumentPZService::DocumentPZService()
{
    model = new DocumentPZModel();
    storeResultService->setIncreasedQuantity();
}

DocumentPZService::~DocumentPZService() {
    delete model;
}

DocumentPZ DocumentPZService::getDocumentPZ(QString symbol) {
    try {
        document = model->getDocumentPZ(symbol);

        document.setRelatedDocuments(relatedDocumentModel->getRelatedDocuments(symbol));

        document.setDocumentPositions(documentPositionService->getPositions(symbol));
    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }

    return document;
}

void DocumentPZService::addDocumentPZ(DocumentPZ document) {
    try {
        Database::getInstance().db.transaction();

        model->addDocumentPZ(document);

        documentPositionService->setStoreResult(document.getStoreResult());
        documentPositionService->addPositions(document.getSymbol(), document.getDocumentPositions());

        Database::getInstance().db.commit();
    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }
}

void DocumentPZService::editDocumentPZ(DocumentPZ newDocument) {
    try {
        Database::getInstance().db.transaction();

        DocumentPZ oldDocument = this->getDocumentPZ(newDocument.getSymbol());
        model->editDocumentPZ(newDocument);

        documentPositionService->setStoreResult(newDocument.getStoreResult());
        documentPositionService->updateDocumentPositions(oldDocument, newDocument);

        Database::getInstance().db.commit();
    } catch(SQLException *e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
}

void DocumentPZService::removeDocument(QString symbol, bool cancelStoreResult) {
    try {
        Database::getInstance().db.transaction();

        model->removeDocument(symbol);
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
