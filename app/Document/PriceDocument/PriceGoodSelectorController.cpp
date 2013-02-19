#include "PriceGoodSelectorController.h"

PriceGoodSelectorController::PriceGoodSelectorController(QWidget* parent, QString symbol)
{
    this->symbol = symbol;
    this->view = new SelectGoodView(parent,this);
    this->goodsTVStandardModel = new GoodsTVStandardItemModel();
    initStartConf();
    this->getView()->getMarkAll()->show();
}

PriceGoodSelectorController::~PriceGoodSelectorController() {
    delete goodsTVStandardModel;
}

void PriceGoodSelectorController::initGoodsTable(){
    goodsTVStandardModel->getGoods();
    view->getGoodsTable()->setGoodsModel(goodsTVStandardModel);

    int colCount = getView()->getGoodsTable()->model()->rowCount();
    emit rowCountChanged(colCount);
}

void PriceGoodSelectorController::selectGoods(){
}

bool PriceGoodSelectorController::isChecked(int row){
    return this->goodsTVStandardModel->item(row,1)->checkState() == Qt::Checked;
}

QVector<Goods> *PriceGoodSelectorController::getGoods() {

    QVector<Goods> *goods = new QVector<Goods>();

    int rows = this->getView()->getGoodsTable()->model()->rowCount();
    for(int i=0; i < rows; i++) {
        if(isChecked(i)) {
            int id = this->getView()->getGoodsTable()->model()->index(i,0).data().toInt();
            goods->append(this->getGoodsService()->getGood(id));
        }
    }
    return goods;
}

void PriceGoodSelectorController::markAllItems(bool mark) {
    mark ?
    setTableItemsChecked(Qt::Checked) :
    setTableItemsChecked(Qt::Unchecked);
    view->getGoodsTable()->setGoodsModel(goodsTVStandardModel);
}

void PriceGoodSelectorController::setTableItemsChecked(Qt::CheckState action) {
    for(int i = 0; i < goodsTVStandardModel->rowCount(); i++) {
        goodsTVStandardModel->item(i,1)->setCheckState(action);
    }
}

void PriceGoodSelectorController::showingMarkAll(int count) {
    if(count == 0)
        getView()->getMarkAll()->hide();
    else
        getView()->getMarkAll()->show();
}

void PriceGoodSelectorController::setTaxForRRFilter(int idTax)
{
    goodsTVStandardModel->setTaxForRRFilter(idTax);
    initGoodsTable();
}

void PriceGoodSelectorController::setGoodsNameFilter(QString text)
{
    goodsTVStandardModel->setNameFilter(text);
    initGoodsTable();
}

void PriceGoodSelectorController::setGoodsSymbolFilter(QString text)
{
    goodsTVStandardModel->setSymbolFilter(text);
    initGoodsTable();
}

void PriceGoodSelectorController::setGoodsGoodGroupFilter(int id) {

    QVariant value = view->getChooseGoodGroup()->itemData(id);
    goodsTVStandardModel->setGoodsGroupFilter(value.toInt());
    initGoodsTable();
}
