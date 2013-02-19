#include "SelectInvoiceController.h"

SelectInvoiceController::SelectInvoiceController(QWidget* parent)
{
    this->init(parent, "SALE");
}

SelectInvoiceController::SelectInvoiceController(QWidget* parent, QStringList docTypeFilter)
{
    this->docTypeFilter = docTypeFilter;
    this->init(parent, "SALE");
}

SelectInvoiceController::SelectInvoiceController(QWidget* parent, QString documentFamily)
{
    this->init(parent, documentFamily);
}

void SelectInvoiceController::init(QWidget* parent, QString documentFamily)
{
    this->view = new SelectInvoiceView(parent, this);

    if(documentFamily == "SALE")
        documentTVModel = new SaleDocumentTVModel();
    else if(documentFamily == "PURCHASE")
        documentTVModel = new PurchaseDocumentTVModel();

    initInvoiceTable();

    selectColumnsDialog = new SelectVisibleColumns(view->getInvoiceTable());
    connect(selectColumnsDialog, SIGNAL(selectedColumnsChanged(QList<int>)), this, SLOT(changeColumnVisiblity(QList<int>)));

    restoreTableState();
}

void SelectInvoiceController::setDocumentNotTypeFilter(QString excludedType)
{
    documentTVModel->setDocNotTypeFilter(excludedType);
    documentTVModel->getDocuments();
}

SelectInvoiceController::~SelectInvoiceController()
{
    saveTableState();
    delete documentTVModel;
}

Document SelectInvoiceController::addInvoice()
{
    Document invoice;
    QString symbol = view->getInvoiceTable()->getSymbol();

    if(!symbol.isEmpty())
    {
        if(symbol.contains("FV")||symbol.contains("PRO")||symbol.contains("FMP"))
        {
            InvoiceService *service = new InvoiceService();
            invoice = (Document) service->getInvoice(symbol);
            delete service;
        }
        else if(symbol.contains("FZ"))
        {
            PurchaseInvoiceService* service = new PurchaseInvoiceService();
            invoice = (Document) service->getPurchaseInvoice(symbol);
            delete service;
        }
        else if(symbol.contains("ZAL")||symbol.contains("RZL"))
        {
            DocumentZALService* service = new DocumentZALService();
            invoice = (Document)service->getDocumentZAL("symbol");
            delete service;
        }
    }
    return invoice;
}


void SelectInvoiceController::showDialog()   {
    view->exec();
}

int SelectInvoiceController::getCancel(){
    return cancel;
}

SelectInvoiceView *SelectInvoiceController::getView(){
    return view;
}

void SelectInvoiceController::setCancel ()
{
    cancel=1;
}

void SelectInvoiceController::initInvoiceTable()
{
    documentTVModel->setDocTypeFilter(docTypeFilter);
    documentTVModel->getDocuments();
    view->getInvoiceTable()->setSaleDocumentModel(documentTVModel);
}

void SelectInvoiceController::dialogSelectColumns() {
    selectColumnsDialog->exec();
}

void SelectInvoiceController::changeColumnVisiblity(QList<int> visibleColumns)
{
    for(int column = 0; column < view->getInvoiceTable()->model()->columnCount(); column++) {
        if(visibleColumns.contains(column))
            view->getInvoiceTable()->setColumnHidden(column, false);
        else
            view->getInvoiceTable()->setColumnHidden(column, true);
    }
}

void SelectInvoiceController::restoreTableState() {
    tableStateManager = new TableStateManager();

    QByteArray state = tableStateManager->getState("SELECT_WINDOW_INVOICE");
    view->getInvoiceTable()->horizontalHeader()->restoreState(state);

    view->getInvoiceTable()->hideIdColumn(); // ukrywa id
    view->getInvoiceTable()->horizontalHeader()->setSortIndicatorShown(true); // pokazuje sortindicator

    int columnAtTable = view->getInvoiceTable()->horizontalHeader()->sortIndicatorSection();
    documentTVModel->sortByColumn(columnAtTable, view->getInvoiceTable()->horizontalHeader()->sortIndicatorOrder());
    documentTVModel->getDocuments();

    delete tableStateManager;
}

void SelectInvoiceController::saveTableState() {
    tableStateManager = new TableStateManager();

    QByteArray state = view->getInvoiceTable()->horizontalHeader()->saveState();
    QByteArray oldState = tableStateManager->getState("SELECT_WINDOW_INVOICE");
    if(state != oldState)
        tableStateManager->saveState("SELECT_WINDOW_INVOICE", state);

    delete tableStateManager;
}

void SelectInvoiceController::setDocumentSymbolFilter(QString text)
{
    documentTVModel->setSymbolFilter(text);
    documentTVModel->getDocuments();
}
