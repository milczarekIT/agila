#include "StorageService.h"

StorageService::StorageService()
{
    model = new StorageModel();
    storeResultService->setIncreasedQuantity();
}

StorageService::~StorageService() {
    delete model;
}

StoreDocument StorageService::getStoreDocument(QString symbol) {
    try {
        document = model->getStoreDocument(symbol);

        document.setRelatedDocuments(relatedDocumentModel->getRelatedDocuments(symbol));

        document.setDocumentPositions(documentPositionService->getPositions(symbol));

    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }

    return document;
}

void StorageService::addStoreDocument(StoreDocument document) {
    try {
        Database::getInstance().db.transaction();

        model->addStoreDocument(document);
        if(document.getDocumentType() == "PW" || document.getDocumentType() == "PZ")
            storeResultService->setIncreasedQuantity();
        else if(document.getDocumentType() == "WZ" || document.getDocumentType() == "RW")
            storeResultService->setDecreasedQuantity();

        documentPositionService->setStoreResult(document.getStoreResult());
        documentPositionService->addPositions(document.getSymbol(), document.getDocumentPositions());

        Database::getInstance().db.commit();
    } catch(SQLException *e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
}

void StorageService::editStoreDocument(StoreDocument newDocument) {
    try {
        Database::getInstance().db.transaction();

        StoreDocument oldDocument = this->getStoreDocument(newDocument.getSymbol());
        model->editStoreDocument(newDocument);

        documentPositionService->setStoreResult(newDocument.getStoreResult());
        documentPositionService->updateDocumentPositions(oldDocument, newDocument);

        Database::getInstance().db.commit();
    } catch(SQLException *e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
}

void StorageService::removeDocument(QString symbol, bool cancelStoreResult) {
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
