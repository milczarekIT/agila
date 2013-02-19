#include "OfferController.h"

OfferController::OfferController(QObject *parent) : PriceDocumentController(parent) {
    view = new OfferView(this);
    service = new OfferService();
    goods = new QVector<Goods>();
    initTableModel();
    initPriceLevel();
}

OfferController::~OfferController() {
    delete service;
}

int OfferController::exec(QString symbol) {
    pList = service->getOffer(symbol);

    c = pList.getContractor();
    getView()->getSign()->setText(pList.getSymbol());
    getView()->getCreateDate()->setDate(pList.getDocumentDate());
    getView()->getContractorData()->setText(pList.getContractor().getContractorData());
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

void OfferController::add() {
    getView()->getSign()->setText(getNextSymbol());
    edition = false;
    int ret = PriceDocumentController::exec();

    if(ret == QDialog::Accepted) {
        PriceList list = getDataFromView();
        service->addOffer(list);
    }
}

void OfferController::edit(QString symbol) {
    edition = true;
    int ret = this->exec(symbol);
    if(ret == QDialog::Accepted) {
        PriceList list = getDataFromView();
        service->editOffer(list);
    }
}

void OfferController::selectContractor() {
    SelectContractorController* contractorSelect = new SelectContractorController(view);
    contractorSelect->showDialog();

    if(contractorSelect->getView()->getContractorsTable()->getId() > 0) {
        c = contractorSelect->addContractor();
        view->getContractorData()->setText(c.getContractorData());
    }
    delete contractorSelect;
}

PriceList OfferController::getDataFromView() {
    PriceList list;
    list.setDocumentType(view->getSymbol());
    list.setSymbol(view->getSign()->text());
    list.setDocumentDate(view->getCreateDate()->date());
    list.setDocumentPositions(getDocumentPositions());
    list.setContractor(c);

    if(!view->getNotConcerns()->isChecked()) {
        list.setValidFromDate(view->getDateFrom()->date());
        list.setValidToDate(view->getDateTo()->date());
    }

    initTableModel();
    return list;
}

QString OfferController::getNextSymbol() {
    documentNumerator = new DocumentNumeratorController("OF");
    QString nextSymbol = documentNumerator->getNextSymbol();
    delete documentNumerator;

    return nextSymbol;
}
