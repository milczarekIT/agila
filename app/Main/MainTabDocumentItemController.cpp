#include "MainTabDocumentItemController.h"

MainTabDocumentItemController::MainTabDocumentItemController()
{
    tableStateManager = new TableStateManager();
}

MainTabDocumentItemController::~MainTabDocumentItemController() {
    delete tableStateManager;
}

void MainTabDocumentItemController::setFromDateFilter(QDate fromDate)
{
    documentTVModel->setFromDateFilter(fromDate);
    documentTVModel->getDocuments();
}

void MainTabDocumentItemController::setToDateFilter(QDate toDate)
{
    documentTVModel->setToDateFilter(toDate);
    documentTVModel->getDocuments();
}

void MainTabDocumentItemController::setDocTypeFilter(QString documentType)
{
    documentTVModel->setDocTypeFilter(documentType);
    documentTVModel->getDocuments();
}

void MainTabDocumentItemController::dialogSelectColumns() {
    selectColumnsDialog->exec();
}

void MainTabDocumentItemController::refreshTable()
{
    documentTVModel->getDocuments();
}
