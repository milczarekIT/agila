#include "OrderService.h"

OrderService::OrderService()
{
    model = new OrderModel();
}

OrderService::~OrderService() {
    delete model;
}

Order OrderService::getOrder(QString symbol) {
    try {
       order = model->getOrder(symbol);

        order.setRelatedDocuments(relatedDocumentModel->getRelatedDocuments(symbol));

        order.setDocumentPositions(documentPositionService->getPositions(symbol));
    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }

    return order;
}

void OrderService::addOrder(Order order) {
    try {
        Database::getInstance().db.transaction();

        model->addOrder(order);

        documentPositionService->setStoreResult(order.getStoreResult());
        documentPositionService->addPositions(order.getSymbol(), order.getDocumentPositions());

        Database::getInstance().db.commit();
    } catch(SQLException *e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
}

void OrderService::editOrder(Order newOrder) {
    try {
        Database::getInstance().db.transaction();

        Order oldOrder = this->getOrder(newOrder.getSymbol());
        model->editOrder(newOrder);

        documentPositionService->setStoreResult(newOrder.getStoreResult());
        documentPositionService->updateDocumentPositions(oldOrder, newOrder);

        Database::getInstance().db.commit();
    } catch(SQLException *e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
}

void OrderService::removeOrder(QString symbol) {
    try {
        Database::getInstance().db.transaction();

        model->removeOrder(symbol);

        documentPositionService->removePositions(symbol);
        relatedDocumentModel->removeLinksToDocument(symbol);

        Database::getInstance().db.commit();
    } catch(SQLException *e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
}
