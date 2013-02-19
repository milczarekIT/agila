#include "DocumentWZService.h"

DocumentWZService::DocumentWZService()
{
    model = new DocumentWZModel();
    storeResultService->setDecreasedQuantity();
}

DocumentWZService::~DocumentWZService() {
    delete model;
}

DocumentWZ DocumentWZService::getDocumentWZ(QString symbol) {
    try {
        document = model->getDocumentWZ(symbol);

        document.setRelatedDocuments(relatedDocumentModel->getRelatedDocuments(symbol));

        DocumentInfoModel *documentInfoModel = new DocumentInfoModel();
        foreach(SimpleDocumentInfo info, document.getRelatedDocuments())
        {
            QString documentFamily = documentInfoModel->getDocumentFamilyBySymbol(info.getSymbol()).getId();
            if(documentFamily != "CASH" && documentFamily != "PURCHASE" && documentFamily != "ORDER" && documentFamily != "OTHER" && documentFamily != "STORE")
            { // dozwolony sale lub niezdefiniowany (gdy np. nr faktury nie znajduje się w Agili
                document.setFactureSymbol(info.getSymbol());
                break;
            }
        }
        delete documentInfoModel;

        document.setDocumentPositions(documentPositionService->getPositions(symbol));
    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }

    return document;
}

void DocumentWZService::addDocumentWZ(DocumentWZ document) {
    try {
        Database::getInstance().db.transaction();

        model->addDocumentWZ(document);

        relatedDocumentModel->addLinkToDocument(document.getFactureSymbol(), document.getSymbol());
        documentPositionService->setStoreResult(document.getStoreResult());
        documentPositionService->addPositions(document.getSymbol(), document.getDocumentPositions());

        Database::getInstance().db.commit();
    } catch(SQLException *e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
}

void DocumentWZService::editDocumentWZ(DocumentWZ newDocument) {
    try {
        Database::getInstance().db.transaction();

        DocumentWZ oldDocument = this->getDocumentWZ(newDocument.getSymbol());
        model->editDocumentWZ(newDocument);

        documentPositionService->setStoreResult(newDocument.getStoreResult());
        documentPositionService->updateDocumentPositions(oldDocument, newDocument);
        relatedDocumentModel->editLinkToBaseDocument(newDocument.getFactureSymbol(), newDocument.getSymbol());

        Database::getInstance().db.commit();
    } catch(SQLException *e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
}

void DocumentWZService::removeDocument(QString symbol, bool cancelStoreResult) {
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
