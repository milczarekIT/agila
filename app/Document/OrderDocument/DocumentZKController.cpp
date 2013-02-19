#include "DocumentZKController.h"

DocumentZKController::DocumentZKController(QWidget* parent, QString symbol, bool edit) {
    this->symbol = symbol;
    this->edition = edit;
    this->view = new DocumentZKView(parent,this);
    this->validator = new DocumentValidator(view,symbol);
    this->orderService = new OrderService();
    this->managerOrd = new OrderManager();
    this->manager=managerOrd;
    this->smodel = new SettingsModel();
    changingContractor=false;
}

DocumentZKController::~DocumentZKController()
{
    delete orderService;
}

void DocumentZKController::exec ()
{
    dnc = new DocumentNumeratorController(symbol);
    QString nextSymbol = dnc->getNextSymbol();
    view->getLineDocumentSymbol()->setText(nextSymbol);
    delete dnc;
    view->disablePrintButton(true);
    dnc = NULL;

    QString documentPlace = smodel->getDefualtDocumentPlace().getName();
    this->view->setLineDocumentPlace(documentPlace);

    this->view->setLineIssueName(""); //TODO dane użytkownika programu!!!!!!!!!!!!!!!!!

    if (view->exec())
    {
        getOrderData();
        orderService->addOrder(managerOrd->getOrder());
        return;
    }
    return;
}

void DocumentZKController::exec(QString Symbol)
{
    this->edition = true;
    managerOrd->setOrder(orderService->getOrder(Symbol));
    managerOrd->setOrderOld(managerOrd->getOrder());
    view->setLineDocumentSymbol(managerOrd->getOrder().getSymbol());
    view->setLineDocumentPlace(managerOrd->getOrder().getDocumentPlace());
    view->setDateIssue(managerOrd->getOrder().getDocumentDate());
    view->setRealizationDate(managerOrd->getOrder().getRealizationDate());
    view->setRealized(managerOrd->getOrder().isRealized());
    view->setLineDiscount(managerOrd->getOrder().getDiscount());
    view->setLineReceiveName(managerOrd->getOrder().getReceiveName());
    view->setLineIssueName(managerOrd->getOrder().getIssueName());
    view->setLineDocumentSymbol(managerOrd->getOrder().getSymbol());
    managerOrd->setContractor(managerOrd->getOrder().getContractor());
    managerOrd->setDocumentPositions(managerOrd->getOrder().getDocumentPositions());
    addGood();
    addContractor();

    if (view->exec())
    {
        getOrderData();
        if(this->isChangesOccured())
        {
        orderService->editOrder(managerOrd->getOrder());
         }
    }
}

void DocumentZKController::getOrderData()
{
    Order order;
    order.setDocumentType(symbol);
    order.setSymbol(view->getLineDocumentSymbol()->text());
    order.setDocumentPlace(view->getLineDocumentPlace()->text());
    order.setDocumentDate(view->getDateIssue());
    order.setRealizationDate(view->getRealizationDate());
    order.setTotal(view->getLineGoodsValue());
    order.setDiscount(view->getLineDiscount()->text().toFloat());
    order.setReceiveName(view->getLineReceiveName());
    order.setIssueName(view->getLineIssueName());
    order.setRealized(view->isRealized());
    managerOrd->setOrderData(order);
}

bool DocumentZKController::isChangesOccured() {
    return !(managerOrd->getOrderOld() == managerOrd->getOrder());
}

void DocumentZKController::checkChanges()
{
    getOrderData();

    if(validator->isEmptyForm())
        view->reject();

   else if(isChangesOccured())
    {
        MessageBox *messageBox = new MessageBox();
        if (messageBox->createQuestionBox("Dokonano zmian") == MessageBox::YES)
           validator->validateDocForm(edition);
        else
            view->reject(); // zmiany dokonane, ale użytkowik chce anulować
    }
    else
         view->reject(); // nie dokonano zmian, anuluj
}


