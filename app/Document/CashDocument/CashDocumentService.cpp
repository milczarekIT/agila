#include "CashDocumentService.h"

CashDocumentService::CashDocumentService()
{
    model = new CashDocumentModel();
}

CashDocumentService::~CashDocumentService() {
    delete model;
}

CashDocument CashDocumentService::getCashDocument(QString symbol) {
    try {
        Database::getInstance().db.transaction();

        document = model->getCashDocument(symbol);

        document.setRelatedDocuments(relatedDocumentModel->getRelatedDocuments(symbol));

        Database::getInstance().db.commit();
    } catch(SQLException *e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }

    return document;
}

void CashDocumentService::addCashDocument(CashDocument document) {
    try {
        Database::getInstance().db.transaction();

        model->addCashDocument(document);

        Database::getInstance().db.commit();
    } catch(SQLException *e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
}

void CashDocumentService::editCashDocument(CashDocument newDocument) {
    try {
        Database::getInstance().db.transaction();

        model->editCashDocument(newDocument);

        Database::getInstance().db.commit();
    } catch(SQLException *e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
}

void CashDocumentService::removeCashDocument(QString symbol) {
    try {
        Database::getInstance().db.transaction();

        model->removeCashDocument(symbol);

        relatedDocumentModel->removeLinksToDocument(symbol);

        Database::getInstance().db.commit();
    } catch(SQLException *e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
}
