#include "SelectOrderController.h"

SelectOrderController::SelectOrderController(QWidget* parent,QString docTypeFilter)
{
    this->docTypeFilter=docTypeFilter;
    this->init(parent);

}


void SelectOrderController::init(QWidget* parent)
{

    this->view = new SelectInvoiceView(parent, this);
    view->setWindowTitle("Wybierz zamówienie");
    orderDocumentTVModel = new OrderDocumentTVModel();
    initOrderTable();

    selectColumnsDialog = new SelectVisibleColumns(view->getInvoiceTable());
    connect(selectColumnsDialog, SIGNAL(selectedColumnsChanged(QList<int>)), this, SLOT(changeColumnVisiblity(QList<int>)));

    restoreTableState();
}

SelectOrderController::~SelectOrderController()
{
    saveTableState();
    delete orderDocumentTVModel;
}

Order SelectOrderController::addOrder()
{
    Order order;
    QString symbol = view->getInvoiceTable()->getSymbol();

    if(!symbol.isEmpty())
    {

            OrderService *service = new OrderService();
            order = service->getOrder(symbol);
            delete service;
        }

    return order;
}

void SelectOrderController::showDialog()   {
    view->exec();
}

int SelectOrderController::getCancel(){
    return cancel;
}

SelectInvoiceView *SelectOrderController::getView(){
    return view;
}

void SelectOrderController::setCancel ()
{
    cancel=1;
}

void SelectOrderController::initOrderTable()
{
    orderDocumentTVModel->setDocTypeFilter(docTypeFilter);
    orderDocumentTVModel->getDocuments();
    view->getInvoiceTable()->setOrderDocumentModel(orderDocumentTVModel);
}

void SelectOrderController::dialogSelectColumns() {
    selectColumnsDialog->exec();
}

void SelectOrderController::changeColumnVisiblity(QList<int> visibleColumns)
{
    for(int column = 0; column < view->getInvoiceTable()->model()->columnCount(); column++) {
        if(visibleColumns.contains(column))
            view->getInvoiceTable()->setColumnHidden(column, false);
        else
            view->getInvoiceTable()->setColumnHidden(column, true);
    }
}

void SelectOrderController::restoreTableState() {
    tableStateManager = new TableStateManager();
    QByteArray state = tableStateManager->getState("SELECT_WINDOW_ORDER");
    view->getInvoiceTable()->horizontalHeader()->restoreState(state);

    view->getInvoiceTable()->hideIdColumn(); // ukrywa id
    view->getInvoiceTable()->horizontalHeader()->setSortIndicatorShown(true); // pokazuje sortindicator

    delete tableStateManager;
}

void SelectOrderController::saveTableState() {
    tableStateManager = new TableStateManager();
    QByteArray state = view->getInvoiceTable()->horizontalHeader()->saveState();
    QByteArray oldState = tableStateManager->getState("SELECT_WINDOW_ORDER");
    if(state != oldState)
        tableStateManager->saveState("SELECT_WINDOW_ORDER", state);

    delete tableStateManager;
}
