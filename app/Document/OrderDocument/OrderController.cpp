#include "OrderController.h"

OrderController::OrderController(QWidget* parent, QString symbol, bool edit) {

    this->symbol = symbol;
    this->edition = edit;
    this->view = new OrderView(parent,this);
    this->validator = new DocumentValidator(view,symbol);
    this->orderService = new OrderService();
    this->manager = new OrderManager();
    changingContractor=false;
    restoreTableState();
}

OrderController::~OrderController()
{
    saveTableState();
    delete orderService;
    delete validator;
    delete manager;
}

void OrderController::exec ()
{
    dnc = new DocumentNumeratorController(symbol);
    QString nextSymbol = dnc->getNextSymbol();
    view->getLineDocumentSymbol()->setText(nextSymbol);
    delete dnc;
    dnc = NULL;

    QString documentPlace = smodel->getDefualtDocumentPlace().getName();
    this->view->setLineDocumentPlace(documentPlace);

    this->view->setLineIssueName(""); //TODO dane użytkownika programu!!!!!!!!!!!!!!!!!

    if (view->exec())
    {
        getDocumentData();
        orderService->addOrder(manager->getOrderPolicy()->getOrder());
        printDoc();
        return;
    }
    return;
}

void OrderController::exec(QString Symbol)
{
    this->edition = true;
    this->totalFromBase = true;
    manager->getOrderPolicy()->setOrder(orderService->getOrder(Symbol));
    manager->getOrderPolicy()->setOrderOld(manager->getOrderPolicy()->getOrder());
    view->setLineDocumentSymbol(manager->getOrderPolicy()->getOrder().getSymbol());
    view->setLineDocumentPlace(manager->getOrderPolicy()->getOrder().getDocumentPlace());
    view->setDateIssue(manager->getOrderPolicy()->getOrder().getDocumentDate());
    view->setRealizationDate(manager->getOrderPolicy()->getOrder().getRealizationDate());
    view->setRealized(manager->getOrderPolicy()->getOrder().isRealized());
    view->setLineDiscount(manager->getOrderPolicy()->getOrder().getDiscount());
    view->setLineReceiveName(manager->getOrderPolicy()->getOrder().getReceiveName());
    view->setLineIssueName(manager->getOrderPolicy()->getOrder().getIssueName());
    view->setLineDocumentSymbol(manager->getOrderPolicy()->getOrder().getSymbol());
    manager->setContractor(manager->getOrderPolicy()->getOrder().getContractor());
    manager->setDocumentPositions(manager->getOrderPolicy()->getOrder().getDocumentPositions());
    addGood();
    addContractor();
    if(totalFromBase==true)
    {
    view->setLineGoodsValueDiscount(manager->getOrderPolicy()->getOrder().getTotal());
    totalFromBase=false;
    }

    if (view->exec())
    {
        getDocumentData();
        if(this->isChangesOccured())
        {
        orderService->editOrder(manager->getOrderPolicy()->getOrder());
        printDoc();
         }
    }
}

void OrderController::getDocumentData()
{
    Order order;
    order.setDocumentType(symbol);
    order.setSymbol(view->getLineDocumentSymbol()->text());
    order.setDocumentPlace(view->getLineDocumentPlace()->text());
    order.setDocumentDate(view->getDateIssue());
    order.setRealizationDate(view->getRealizationDate());
    order.setTotal(view->getLineGoodsValueDiscount());
    order.setDiscount(view->getDiscountOrWaybillNo()->text().toDouble());
    order.setReceiveName(view->getLineReceiveName());
    order.setIssueName(view->getLineIssueName());
    order.setRealized(view->isRealized());
    order.setDocumentPositions(manager->getDocumentPosition());
    manager->getOrderPolicy()->setOrderData(order);
}

bool OrderController::isChangesOccured() {
    return !(manager->getOrderPolicy()->getOrderOld() == manager->getOrderPolicy()->getOrder());
}

void OrderController::printDoc()
{
      PrintOrderDocumentController *pc = new PrintOrderDocumentController(view->getLineDocumentSymbol()->text());
      Order doc = orderService->getOrder(view->getLineDocumentSymbol()->text());
      pc->print(&doc);
      delete pc;
}

void OrderController::changedRealizedOrSymbol()
{
 if(view->getRealizationDate()<=view->getDateIssue())
    view->setRealized(true);
 else
    view->setRealized(false);
}

void OrderController::restoreTableState() {
    QByteArray state = tableStateManager->getState("ORDER_TABLE_GOODS");
    view->getGoodsTable()->horizontalHeader()->restoreState(state);
}

void OrderController::saveTableState() {
    QByteArray state = view->getGoodsTable()->horizontalHeader()->saveState();
    QByteArray oldState = tableStateManager->getState("ORDER_TABLE_GOODS");
    if(state != oldState)
        tableStateManager->saveState("ORDER_TABLE_GOODS", state);
}


