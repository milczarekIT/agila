#include "MainTabGoodsItemController.h"

MainTabGoodsItemController::MainTabGoodsItemController()
{
    view = new MainTabGoodsItem(this);
    goodsService = new GoodsService();
    model = new GoodsTVModel();
    initModel();
    initComboBox();

    initSelectingColumnVisibility();
    restoreTableState();
    initPriceFilter();

    if(!ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
        view->getTableView()->setColumnHidden(3, true); // ilość
}

MainTabGoodsItemController::~MainTabGoodsItemController()
{
    saveTableState();
    delete goodsService;
    delete model;
}

MainTabItem *MainTabGoodsItemController::getView()
{
    return view;
}

void MainTabGoodsItemController::dialogGoodsAdd()
{
    GoodsDialogController *dialog = new GoodsDialogController(this);
    connect(dialog->getView(),SIGNAL(settingsChangedSignal(QString)),this,SLOT(settingsChanged(QString)));

    if(dialog->exec())
        model->getGoods();

    delete dialog;
}

void MainTabGoodsItemController::removeGood ()
{

    int id = view->getTableView()->getId();

    if(id==-1)
    {
        MessageBox * msgBox = new MessageBox();
        msgBox->createInfoBox("Zaznacz towar/usługę do usunięcia");
        delete msgBox;
    }
    else{
        GoodsRemoveConfirmativeDialog *dialog = new GoodsRemoveConfirmativeDialog(id, this);
        dialog->exec();
        delete dialog;

        model->getGoods();
    }

}

void MainTabGoodsItemController::setGoodsNameFilter (QString filter)
{
    model->setNameFilter(filter);
    model->getGoods();
}

void MainTabGoodsItemController::setGoodsSymbolFilter (QString filter)
{
    model->setSymbolFilter(filter);
    model->getGoods();
}

void  MainTabGoodsItemController::fillBox(QComboBox *box,QVector<GoodsGroup> values)
{
    for(int i = 0; i < values.size(); i++)
        box->addItem(values[i].getName(), QVariant::fromValue(values[i].getId()));
}

void MainTabGoodsItemController::initComboBox()
{
    GoodsGroupModel *goodsGroupModel = new GoodsGroupModel();
    view->getGoodsGroup()->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    QVector<GoodsGroup> ggroups = goodsGroupModel->getGoodsGroups();
    view->getGoodsGroup()->addItem("Wszystkie", -1);
    view->getGoodsGroup()->addItem("BRAK", 0);
    fillBox(view->getGoodsGroup(), ggroups);
    connect(view->getGoodsGroup(), SIGNAL(currentIndexChanged(int)), this, SLOT(setGoodsGroupFilter(int)));
    delete goodsGroupModel;

    view->getPriceLevel()->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    view->getPriceLevel()->addItem("A", Price::A);
    view->getPriceLevel()->addItem("B", Price::B);
    view->getPriceLevel()->addItem("C", Price::C);
    view->getPriceLevel()->addItem("MAG", Price::MAG);
    connect(view->getPriceLevel(), SIGNAL(currentIndexChanged(int)), this, SLOT(setPriceLevelFilter(int)));

}

void MainTabGoodsItemController::setGoodsGroupFilter(int index)
{
    int goodsGroupId = view->getGoodsGroup()->itemData(index).toInt();

    model->setGoodsGroupFilter(goodsGroupId);
    model->getGoods();
}

void MainTabGoodsItemController::setPriceLevelFilter(int index)
{
    int priceLevel = view->getPriceLevel()->itemData(index).toInt();

    setVisiblePriceLevel(priceLevel);
}

void MainTabGoodsItemController::setVisiblePriceLevel(int priceType)
{
    int previousColumns = 7;

    for(int i = 0; i <= 6; i=i+2)
    {
        if(i == priceType) {

            view->getTableView()->setColumnHidden(previousColumns + i + Price::NET, false);
            view->getTableView()->setColumnHidden(previousColumns + i + Price::GROSS, false);
        }
        else {
            view->getTableView()->setColumnHidden(previousColumns + i + Price::NET, true);
            view->getTableView()->setColumnHidden(previousColumns + i + Price::GROSS, true);
        }
    }
}

int MainTabGoodsItemController::getVisiblePriceLevel() {
    TableView *tv = view->getTableView();
    if(!tv->isColumnHidden(7) && !tv->isColumnHidden(8))
        return Price::A;
    else if(!tv->isColumnHidden(9) && !tv->isColumnHidden(10))
        return Price::B;
    else if(!tv->isColumnHidden(11) && !tv->isColumnHidden(12))
        return Price::C;
    else if(!tv->isColumnHidden(13) && !tv->isColumnHidden(14))
        return Price::MAG;
    else // default
        return Price::A;
}

void MainTabGoodsItemController::initPriceFilter() {
    int index = view->getPriceLevel()->findData(getVisiblePriceLevel());

    view->getPriceLevel()->setCurrentIndex(index);
}

void MainTabGoodsItemController::dialogGoodsEdit()
{
    if(view->getTableView()->getId() > 0)
    {
        GoodsDialogController dialog(this);
        if(dialog.exec(view->getTableView()->getId()))
            model->getGoods();
    }
    else
    {
        MessageBox *messageBox = new MessageBox();
        messageBox->createInfoBox("Zaznacz towar/usługę do edycji");
        delete messageBox;
    }
}

void MainTabGoodsItemController::initModel()
{
    model->getGoods();
    view->getTableView()->setGoodsModel(model);
}

GoodsTVModel *MainTabGoodsItemController::getModel()
{
    return model;
}

void MainTabGoodsItemController::restoreTableState() {
    tableStateManager = new TableStateManager();

    QByteArray state = tableStateManager->getState("MAIN_TAB_GOODS");
    view->getTableView()->horizontalHeader()->restoreState(state);

    view->getTableView()->hideIdColumn(); // ukrywa id
    view->getTableView()->horizontalHeader()->setSortIndicatorShown(true); // pokazuje sortindicator

    int columnAtTable = view->getTableView()->horizontalHeader()->sortIndicatorSection();
    model->sort(columnAtTable, view->getTableView()->horizontalHeader()->sortIndicatorOrder());
    model->getGoods();

    delete tableStateManager;
}

void MainTabGoodsItemController::saveTableState() {
    tableStateManager = new TableStateManager();

    QByteArray state = view->getTableView()->horizontalHeader()->saveState();
    QByteArray oldState = tableStateManager->getState("MAIN_TAB_GOODS");
    if(state != oldState)
        tableStateManager->saveState("MAIN_TAB_GOODS", state);

    delete tableStateManager;
}

void MainTabGoodsItemController::refreshTable()
{
    model->getGoods();
}

void MainTabGoodsItemController::dialogSelectColumns() {
    selectColumnsDialog->exec();
}

void MainTabGoodsItemController::initSelectingColumnVisibility()
{
    selectColumnsDialog = new SelectVisibleColumns(view->getTableView(), this);
    connect(selectColumnsDialog, SIGNAL(selectedColumnsChanged(QList<int>)), this, SLOT(changeColumnVisiblity(QList<int>)));
}

void MainTabGoodsItemController::changeColumnVisiblity(QList<int> visibleColumns)
{
    for(int column = 0; column < view->getTableView()->model()->columnCount(); column++) {
        if(visibleColumns.contains(column))
            view->getTableView()->setColumnHidden(column, false);
        else
            view->getTableView()->setColumnHidden(column, true);
    }
}

void MainTabGoodsItemController::settingsChanged(const QString element)
{
    emit this->settingsChangedSignal(element);
}

ModuleManager::Module MainTabGoodsItemController::module()
{
    return ModuleManager::Goods;
}
