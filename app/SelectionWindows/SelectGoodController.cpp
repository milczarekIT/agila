#include "SelectGoodController.h"

SelectGoodController::SelectGoodController(QWidget* parent, QString symbol)
{
    this->symbol = symbol;
    this->view = new SelectGoodView(parent,this);
    initStartConf();
}

SelectGoodController::SelectGoodController() {
}

SelectGoodController::~SelectGoodController() {
    saveTableState();
    delete goodsTVModel;
    delete goodsService;
}

void SelectGoodController::initStartConf() {

    goodsTVModel = new GoodsTVModel();
    goodsService = new GoodsService();
    //initGoodsTable();
    view->getGoodsTable()->setGoodsModel(goodsTVModel);
    initFilters();

    selectColumnsDialog = new SelectVisibleColumns(view->getGoodsTable());
    connect(selectColumnsDialog, SIGNAL(selectedColumnsChanged(QList<int>)), this, SLOT(changeColumnVisiblity(QList<int>)));

    restoreTableState();

    if(!ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
    {
        // ukrywa kolumnę ilość, jeśli brak modułu Magazyn
        int quantityColumn = this->getQuantityColumn();
        this->view->getGoodsTable()->setColumnHidden(quantityColumn, true);
    }
}

void SelectGoodController::initFilters() {

    GoodsGroupModel *model = new GoodsGroupModel();
    view->getChooseGoodGroup()->addItem("Brak",QVariant(-1));
    fillBox(view->getChooseGoodGroup(),model->getGoodsGroups());

    delete model;
}

void SelectGoodController::fillBox(QComboBox *box,QVector<GoodsGroup> values) {

    for(int i = 0; i < values.size(); i++)
        box->addItem(values[i].getName(), QVariant::fromValue(values[i].getId()));
}

void SelectGoodController::initGoodsTable(){
    goodsTVModel->getGoods();
    view->getGoodsTable()->setGoodsModel(goodsTVModel);
}

Goods SelectGoodController::addGood() {
     Goods good = goodsService->getGood(view->getGoodsTable()->getId());
     return good;
}

void SelectGoodController::dialogGoodsEdit(){
    editGood(view->getGoodsTable()->getId());
}

void SelectGoodController::dialogGoodAdd()
{
    GoodsDialogController dialog(view);
    dialog.exec();
        //update widoku
    initGoodsTable();
}

void SelectGoodController::editGood(int id)
{
    GoodsDialogController dialog(view);
    dialog.exec(id);
        //update widoku
    initGoodsTable();

}

void SelectGoodController::selectGoods() {

    Goods *good = new Goods();
    *good = addGood();
    dialogQuantity = new SelectionNumberOfGoodsController(good,getSymbol());

    int ret = dialogQuantity->exec();
    if (ret == QDialog::Accepted)
       return view->accept();
    else
       return view->repaint();
}

void SelectGoodController::changeColumnVisiblity(QList<int> visibleColumns)
{
    for(int column = 0; column < view->getGoodsTable()->model()->columnCount(); column++) {
        if(visibleColumns.contains(column))
            view->getGoodsTable()->setColumnHidden(column, false);
        else
            view->getGoodsTable()->setColumnHidden(column, true);
    }
}

void SelectGoodController::restoreTableState() {

    tableStateManager = new TableStateManager();
    QByteArray state = tableStateManager->getState("SELECT_WINDOW_GOODS");
    view->getGoodsTable()->horizontalHeader()->restoreState(state);

    view->getGoodsTable()->hideIdColumn(); // ukrywa id
    view->getGoodsTable()->horizontalHeader()->setSortIndicatorShown(true); // pokazuje sortindicator

    int columnAtTable = view->getGoodsTable()->horizontalHeader()->sortIndicatorSection();
    goodsTVModel->sort(columnAtTable, view->getGoodsTable()->horizontalHeader()->sortIndicatorOrder());
    initGoodsTable();

    delete tableStateManager;
}

void SelectGoodController::saveTableState() {

    tableStateManager = new TableStateManager();
    QByteArray state = view->getGoodsTable()->horizontalHeader()->saveState();
    QByteArray oldState = tableStateManager->getState("SELECT_WINDOW_GOODS");
    if(state != oldState)
        tableStateManager->saveState("SELECT_WINDOW_GOODS", state);

    delete tableStateManager;
}

int SelectGoodController::getQuantityColumn() {

    QTableView *table = view->getGoodsTable();
    for(int i = 0; i < table->model()->columnCount(); i++)
    {
        if(table->model()->headerData(i, Qt::Horizontal).toString() == "Ilość")
            return i;
    }

    delete table;
    return -1;
}

void SelectGoodController::setTaxForRRFilter(int idTax)
{
    goodsTVModel->setTaxForRRFilter(idTax);
    goodsTVModel->getGoods();
}
void SelectGoodController::setGoodsNameFilter(QString text)
{
    goodsTVModel->setNameFilter(text);
    initGoodsTable();
}

void SelectGoodController::setGoodsSymbolFilter(QString text)
{
    goodsTVModel->setSymbolFilter(text);
    initGoodsTable();
}

void SelectGoodController::setGoodsGoodGroupFilter(int id) {

    QVariant value = view->getChooseGoodGroup()->itemData(id);
    goodsTVModel->setGoodsGroupFilter(value.toInt());
    initGoodsTable();
}

void SelectGoodController::markAllItems(bool mark) {
}

void SelectGoodController::showingMarkAll(int count) {
}

void SelectGoodController::dialogSelectColumns() {
    selectColumnsDialog->exec();
}

void SelectGoodController::showDialog()   {
    this->view->exec();
}

void SelectGoodController::setCancel () {
    cancel = 1;
}

int SelectGoodController::getCancel() {
    return this->cancel;
}

SelectGoodView *SelectGoodController:: getView() {
    return this->view;
}

QString SelectGoodController::getSymbol() {
    return this->symbol;
}

SelectionNumberOfGoodsController* SelectGoodController::getDialogQuantity() {
    return this->dialogQuantity;
}

GoodsTVModel *SelectGoodController::getGoodsTVModel() {
    return this->goodsTVModel;
}

GoodsService *SelectGoodController::getGoodsService() {
    return this->goodsService;
}
