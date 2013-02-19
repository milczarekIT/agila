#include "DocumentZALService.h"

DocumentZALService::DocumentZALService()
{
    model = new DocumentZALModel();
    storeResultService->setDecreasedQuantity();
}

DocumentZALService::~DocumentZALService()
{
    delete model;
}

DocumentZAL DocumentZALService::getDocumentZAL(QString symbol) {
    try {
        document = model->getDocumentZAL(symbol);

        document.setRelatedDocuments(relatedDocumentModel->getRelatedDocuments(symbol));

        QVector<SimpleDocumentInfo> previousDocumentZAL = this->getPreviousDocumentZAL(relatedDocumentModel->getRelatedDocuments(symbol));
        document.setPreviousDocumentsZAL(previousDocumentZAL);

        document.setDocumentPositions(documentPositionService->getPositions(symbol));
    } catch(SQLException *e) {
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }

    return document;
}

void DocumentZALService::addDocumentZAL(DocumentZAL document) {
    try {
        Database::getInstance().db.transaction();

        model->addDocumentZAL(document);

        documentPositionService->setStoreResult(document.getStoreResult());
        documentPositionService->addPositions(document.getSymbol(), document.getDocumentPositions());
        addLinksToPreviousDocumentsZAL(document.getSymbol(), document.getPreviousDocumentsZAL());

        Database::getInstance().db.commit();
    } catch(SQLException *e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
}

void DocumentZALService::addLinksToPreviousDocumentsZAL(QString actualDocumentZAL, QVector<SimpleDocumentInfo> previousDocumentsZAL)
{
    for(int i = 0; i < previousDocumentsZAL.size(); i++)
        this->relatedDocumentModel->addLinkToDocument(actualDocumentZAL, previousDocumentsZAL[i].getSymbol());
}

void DocumentZALService::editDocumentZAL(DocumentZAL newDocument) {
    try {
        Database::getInstance().db.transaction();

        DocumentZAL oldDocument = this->getDocumentZAL(newDocument.getSymbol());
        model->editDocumentZAL(newDocument);

        documentPositionService->setStoreResult(false);
        documentPositionService->updateDocumentPositions(oldDocument, newDocument);
        editLinksToPreviousDocumentsZAL(newDocument, oldDocument);

        Database::getInstance().db.commit();
    } catch(SQLException *e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
}

void DocumentZALService::editLinksToPreviousDocumentsZAL(DocumentZAL newDocument, DocumentZAL oldDocument)
{
    QVector<SimpleDocumentInfo> newDocPrevDocZAL = newDocument.getPreviousDocumentsZAL();
    QVector<SimpleDocumentInfo> oldDocPrevDocZAL = oldDocument.getPreviousDocumentsZAL();

    if(oldDocPrevDocZAL != newDocPrevDocZAL) // jeśli różne
    {
        for(int i = 0; i < newDocPrevDocZAL.size(); i++)
        {
            if(!relatedDocumentModel->isDocumentSymbolInVector(newDocPrevDocZAL[i].getSymbol(), oldDocPrevDocZAL))
            {
                relatedDocumentModel->addLinkToDocument(newDocument.getSymbol(), newDocPrevDocZAL[i].getSymbol());
                oldDocPrevDocZAL.push_back(newDocPrevDocZAL[i]);
            }
        }
    }

    if(oldDocPrevDocZAL != newDocPrevDocZAL) // jeśli nadal różne tzn. że usunięto ze starego wektora
    {
        for(int i = 0; i < oldDocPrevDocZAL.size(); i++)
        {
            if(!relatedDocumentModel->isDocumentSymbolInVector(oldDocPrevDocZAL[i].getSymbol(), newDocPrevDocZAL))
                this->relatedDocumentModel->removeLinkToDocument(newDocument.getSymbol(), oldDocPrevDocZAL[i].getSymbol());
        }
    }
}

void DocumentZALService::removeDocumentZAL(QString symbol, bool cancelStoreResult) {
    try {
        Database::getInstance().db.transaction();

        model->removeDocumentZAL(symbol);
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

QVector<SimpleDocumentInfo> DocumentZALService::getPreviousDocumentZAL(QVector<SimpleDocumentInfo> relatedDocuments)
{
    QVector<SimpleDocumentInfo> previousDocumentZAL;
    for(int i = 0; i < relatedDocuments.size(); i++) {
        if(relatedDocuments[i].getType() == "ZAL")
            previousDocumentZAL.push_back(relatedDocuments[i]);
    }

    return previousDocumentZAL;
}
