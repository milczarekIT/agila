#include "PriceDocumentController.h"

PriceDocumentController::PriceDocumentController(QObject *parent) : QObject(parent) {
}

PriceDocumentController::~PriceDocumentController() {
    delete goods;
}

int PriceDocumentController::exec() {
    return view->exec();
}

void PriceDocumentController::initPriceLevel() {
    view->getPriceLevel()->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    view->getPriceLevel()->addItem("A", Price::A);
    view->getPriceLevel()->addItem("B", Price::B);
    view->getPriceLevel()->addItem("C", Price::C);
    view->getPriceLevel()->addItem("MAG", Price::MAG);
}

void PriceDocumentController::setCurrentPriceLevel() {
    int priceLevel = pList.getDocumentPositions()[0].getPriceLevel();

    if(priceLevel == Price::A)
        view->getPriceLevel()->setCurrentIndex(0);
    else if(priceLevel == Price::B)
        view->getPriceLevel()->setCurrentIndex(1);
    else if(priceLevel == Price::C)
        view->getPriceLevel()->setCurrentIndex(2);
    else if(priceLevel == Price::MAG)
        view->getPriceLevel()->setCurrentIndex(3);
}

bool PriceDocumentController::isValidateDateNotConcerns() {
    return (pList.getValidFromDate().toString().isEmpty() ||
            pList.getValidToDate().toString().isEmpty());
}

void PriceDocumentController::setDateLikeNotConcerns(bool notConc) {
    view->getDateFrom()->setDisabled(notConc);
    view->getDateTo()->setDisabled(notConc);
}

void PriceDocumentController::updateGoodsSet(QVector<Goods> *choosedGood) {
    for(int i=0; i < choosedGood->size(); i++) {
        Goods g = choosedGood->at(i);
        if(!goods->contains(g)) {
            goods->append(g);
        }
    }
}

void PriceDocumentController::initTableModel() {
    this->getView()->getPositions()->setRowCount(goods->size());
    int priceLevel = view->getPriceLevel()->itemData(view->getPriceLevel()->currentIndex()).toInt();

    for(int i=0; i < goods->size(); i++) {
        this->getView()->getPositions()->setItem(i,0, new QTableWidgetItem(QString::number(goods->value(i).getId())));
        this->getView()->getPositions()->setItem(i,1, new QTableWidgetItem(goods->value(i).getName()));
        this->getView()->getPositions()->setItem(i,2, new QTableWidgetItem(goods->value(i).getSymbol()));
        this->getView()->getPositions()->setItem(i,3, new QTableWidgetItem(goods->value(i).getUnit().getName()));
        this->getView()->getPositions()->setItem(i,4, new QTableWidgetItem(goods->value(i).getPriceNet(priceLevel).toString()));
        this->getView()->getPositions()->setItem(i,5, new QTableWidgetItem(goods->value(i).getPriceGross(priceLevel).toString()));
        this->getView()->getPositions()->setRowHeight(i,25);
    }
}

QVector<DocumentPosition> PriceDocumentController::getDocumentPositions() {
    int priceLevel = view->getPriceLevel()->itemData(view->getPriceLevel()->currentIndex()).toInt();
    QVector<DocumentPosition> documentPositions;
    int iter = goods->size();

    for(int i=0; i<iter; i++) {
        DocumentPosition dp;
        dp.setGood(goods->at(i));
        dp.setPriceLevel(priceLevel);
        dp.setQuantity(0);
        documentPositions.append(dp);
    }

    return documentPositions;
}

QVector<Goods> *PriceDocumentController::getGoodsFromDocumentsPositions(QVector<DocumentPosition> dp) {
    QVector<Goods> *goods = new QVector<Goods>();
    goodsModel = new  GoodsModel();

    for(int i = 0; i < dp.size(); i++) {
        int dpId = dp[i].getGood().getId();
        goods->append(goodsModel->getGood(dpId));
    }

    delete goodsModel;
    return goods;
}

void PriceDocumentController::removeGoodsFromPositions() {
    MessageBox *mb = new MessageBox;

    if(!view->getPositions()->currentIndex().isValid()) {
        mb->createInfoBox("Zaznacz element do usunięcia. ");
    }
    else if(mb->createQuestionBox("Usuwanie dobra. ") == MessageBox::YES) {
        goods->remove(view->getPositions()->currentRow());
    }

    initTableModel();
    delete mb;
}

void PriceDocumentController::selectGoods() {
    PriceGoodSelectorController dialog(view,view->getSymbol());
    dialog.showDialog();

    updateGoodsSet(dialog.getGoods());
    initTableModel();
}

void PriceDocumentController::checkChanges() {

    if(edition) {
        validator = new PriceDocumentsValidator(view);
        if(validator->isEmptyForm())
            view->reject();
        else if(isChangesOccured())
            validator->changesWereMadeMessage();
        else
            view->reject();
        delete validator;
    }
    else view->reject();
}

bool PriceDocumentController::isChangesOccured() {
    return !(pList == getDataFromView());
}

void PriceDocumentController::checkRequiredFields() {
    validator = new PriceDocumentsValidator(view);
    validator->importantDataNoSetMessage(edition);
    delete validator;
}

PriceDocumentView *PriceDocumentController::getView() {
    return view;
}

