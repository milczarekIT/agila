#include "PriceListService.h"

PriceListService::PriceListService() {
    model = new PriceListModel();
}

PriceListService::~PriceListService() {
    delete model;
}

PriceList PriceListService::getPriceList(QString symbol) {
    try {
        priceList = model->getPriceList(symbol);
        priceList.setDocumentPositions(documentPositionService->getPositions(symbol));

    } catch(SQLException *e) {
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
    return priceList;
}

void PriceListService::addPriceList(PriceList list) {

    try {
        Database::getInstance().db.transaction();
        model->addPriceList(list);

        documentPositionService->addPositions(list.getSymbol(), list.getDocumentPositions());

        Database::getInstance().db.commit();

    } catch(SQLException *e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
}

void PriceListService::editPriceList(PriceList newList) {

    try {
        Database::getInstance().db.transaction();

        PriceList oldList = this->getPriceList(newList.getSymbol());
        model->editPriceList(newList);
        qDebug() << newList.getSymbol();
        documentPositionService->updateDocumentPositions(oldList, newList);

        Database::getInstance().db.commit();

    } catch(SQLException *e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
}

void PriceListService::removePriceList(QString symbol) {

    try {
        Database::getInstance().db.transaction();

        model->removePriceList(symbol);

        documentPositionService->removePositions(symbol);

        Database::getInstance().db.commit();

    } catch(SQLException *e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
}
