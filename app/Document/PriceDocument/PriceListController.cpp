#include "PriceListController.h"

PriceListController::PriceListController(QObject *parent) : PriceDocumentController(parent) {
    view = new PriceListView(this);
    service = new PriceListService();
    goods = new QVector<Goods>();
    initTableModel();
    initPriceLevel();
}

PriceListController::~PriceListController() {
    delete service;
}

int PriceListController::exec(QString symbol) {
    pList = service->getPriceList(symbol);

    getView()->getName()->setText(pList.getDocumentName());
    getView()->getSign()->setText(pList.getSymbol());
    getView()->getDescribe()->setText(pList.getDescribe());
    getView()->getCreateDate()->setDate(pList.getDocumentDate());
    setCurrentPriceLevel();

    if(!isValidateDateNotConcerns()) {
        getView()->getDateFrom()->setDate(pList.getValidFromDate());
        getView()->getDateTo()->setDate(pList.getValidToDate());
    } else {
        getView()->getNotConcerns()->setChecked(true);
    }

    goods = getGoodsFromDocumentsPositions(pList.getDocumentPositions());
    initTableModel();
    return PriceDocumentController::exec();
}

void PriceListController::add() {
    edition = false;
    initBasicData();
    int ret = PriceDocumentController::exec();

    if(ret == QDialog::Accepted) {
        PriceList list = getDataFromView();
        service->addPriceList(list);
    }
}

void PriceListController::edit(QString symbol) {
    edition = true;
    int ret = exec(symbol);
    if(ret == QDialog::Accepted) {
        PriceList list = getDataFromView();
        service->editPriceList(list);
    }
}

void PriceListController::initBasicData() {
    QString symbol = getNextSymbol(),
            name = "Cennik " + symbol + " z dnia " + view->getCreateDate()->date().toString();

    getView()->getSign()->setText(symbol);
    getView()->getName()->setText(name);
    getView()->getName()->setCursorPosition(0);
}

PriceList PriceListController::getDataFromView() {
    PriceList list;
    list.setDocumentType(view->getSymbol());
    list.setDocumentName(view->getName()->text());
    list.setSymbol(view->getSign()->text());
    list.setDescribe(view->getDescribe()->toPlainText());
    list.setDocumentDate(view->getCreateDate()->date());
    list.setDocumentPositions(getDocumentPositions());

    if(!view->getNotConcerns()->isChecked()) {
        list.setValidFromDate(view->getDateFrom()->date());
        list.setValidToDate(view->getDateTo()->date());
    }

    return list;
}

QString PriceListController::getNextSymbol() {
    documentNumerator = new DocumentNumeratorController("CN");
    QString nextSymbol = documentNumerator->getNextSymbol();
    delete documentNumerator;

    return nextSymbol;
}

