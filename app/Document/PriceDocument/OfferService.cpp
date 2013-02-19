#include "OfferService.h"

OfferService::OfferService() {
    model = new OfferModel();
}

OfferService::~OfferService() {
    delete model;
}

PriceList OfferService::getOffer(QString symbol) {
    try {
        priceList = model->getOffer(symbol);
        priceList.setDocumentPositions(documentPositionService->getPositions(symbol));

    } catch(SQLException *e) {
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
    return priceList;
}

void OfferService::addOffer(PriceList list) {

    try {
        Database::getInstance().db.transaction();
        model->addOffer(list);

        documentPositionService->addPositions(list.getSymbol(), list.getDocumentPositions());

        Database::getInstance().db.commit();

    } catch(SQLException *e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
}

void OfferService::editOffer(PriceList newList) {

    try {
        Database::getInstance().db.transaction();

        PriceList oldList = this->getOffer(newList.getSymbol());
        model->editOffer(newList);
        qDebug() << newList.getSymbol();
        documentPositionService->updateDocumentPositions(oldList, newList);

        Database::getInstance().db.commit();

    } catch(SQLException *e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
}

void OfferService::removeOffer(QString symbol) {

    try {
        Database::getInstance().db.transaction();

        model->removeOffer(symbol);

        documentPositionService->removePositions(symbol);

        Database::getInstance().db.commit();

    } catch(SQLException *e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
}
