#include "DocumentNKService.h"

DocumentNKService::DocumentNKService()
{
    model = new DocumentNKModel();
}

DocumentNKService::~DocumentNKService() {
    delete model;
}

DocumentNK DocumentNKService::getDocumentNK(QString symbol) {
    try {
        document = model->getDocumentNK(symbol);

        document.setRelatedDocuments(relatedDocumentModel->getRelatedDocuments(symbol));

    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }

    return document;
}

void DocumentNKService::addDocumentNK(DocumentNK document) {
    try {
        Database::getInstance().db.transaction();

        model->addDocumentNK(document);

        if(relatedDocumentModel->isDocumentInApp(document.getInvoiceSymbol()))
            relatedDocumentModel->addLinkToDocument(document.getInvoiceSymbol(), document.getSymbol());

        Database::getInstance().db.commit();
    } catch(SQLException *e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
}

void DocumentNKService::editDocumentNK(DocumentNK newDocument) {
    try {
        Database::getInstance().db.transaction();

        model->editDocumentNK(newDocument);

        if(relatedDocumentModel->isDocumentInApp(newDocument.getInvoiceSymbol()))
            relatedDocumentModel->editLinkToBaseDocument(newDocument.getInvoiceSymbol(), newDocument.getSymbol());

        Database::getInstance().db.commit();
    } catch(SQLException *e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
}

void DocumentNKService::removeDocumentNK(QString symbol) {
    try {
        Database::getInstance().db.transaction();

        model->removeDocumentNK(symbol);

        relatedDocumentModel->removeLinksToDocument(symbol);

        Database::getInstance().db.commit();
    } catch(SQLException *e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
}
