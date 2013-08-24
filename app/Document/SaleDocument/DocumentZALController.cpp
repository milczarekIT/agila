#include "DocumentZALController.h"

DocumentZALController::DocumentZALController(QWidget* parent, QString symbol, bool edit) {
    this->symbol = symbol;
    this->edition = edit;
    this->view = new DocumentZALView(parent,this);
    this->zalService = new DocumentZALService();
    this->mopModel = new MOPModel();
    this->manager= new DocumentZALManager();
    this->validator = new DocumentValidator(view,symbol);
    fillBox(view->getWayToPay(),mopModel->getMethodsOfPayment());
    changingContractor=false;
    restoreTableState();
    changedRealizedOrSymbol();
}

DocumentZALController::~DocumentZALController()
{
    saveTableState();
    delete zalService;
    delete validator;
    delete manager;
    delete mopModel;
}

void DocumentZALController::exec()
{    
    QString documentPlace = smodel->getDefualtDocumentPlace().getName();
    this->view->setLineDocumentPlace(documentPlace);

    if(ApplicationManager::getInstance()->getLoggedUser() != NULL)
        this->view->setLineIssueName(ApplicationManager::getInstance()->getLoggedUser()->getName()); //TODO dane użytkownika programu!!!!!!!!!!!!!!!!!

    if (view->exec())
    {
        getDocumentData();
        zalService->addDocumentZAL(manager->getDocumentZALPolicy()->getDocumentZAL());
        this->printDoc();
        return;
    }
    return;
}

void DocumentZALController::changedRealizedOrSymbol()
{
    if(edition == false)
    {
    QString sym =view->getComboBox()->currentText();
    dnc = new DocumentNumeratorController(sym);
    QString nextSymbol = dnc->getNextSymbol();
    view->getLineDocumentSymbol()->setText(nextSymbol);
    delete dnc;
    dnc = NULL;
    }
}

void DocumentZALController::exec(QString symbol)
{
    this->edition = true;
    this->totalFromBase=true;
    manager->getDocumentZALPolicy()->setDocumentZAL(zalService->getDocumentZAL(symbol));
    manager->getDocumentZALPolicy()->setOldDocumentZAL(manager->getDocumentZALPolicy()->getDocumentZAL());
    manager->setContractor(manager->getDocumentZALPolicy()->getDocumentZAL().getContractor());
    view->setLineDocumentSymbol(manager->getDocumentZALPolicy()->getDocumentZAL().getSymbol());
    view->getWayToPay()->setCurrentIndex(view->getWayToPay()->findData(QVariant::fromValue(manager->getDocumentZALPolicy()->getDocumentZAL().getMethodOfPayment().getId())));
    view->setLineDocumentPlace(manager->getDocumentZALPolicy()->getDocumentZAL().getDocumentPlace());
    view->setDateIssue(manager->getDocumentZALPolicy()->getDocumentZAL().getDocumentDate());
    view->setSaleOrStoreDate(manager->getDocumentZALPolicy()->getDocumentZAL().getSaleDate());
    view->setPaymentDate(manager->getDocumentZALPolicy()->getDocumentZAL().getPaymentDate());
    view->setLineDiscount(manager->getDocumentZALPolicy()->getDocumentZAL().getDiscount());
    view->setLineIssueName(manager->getDocumentZALPolicy()->getDocumentZAL().getIssueName());
    view->setLineReceiveName(manager->getDocumentZALPolicy()->getDocumentZAL().getReceiveName());
    view->setCheckPaid(manager->getDocumentZALPolicy()->getDocumentZAL().isPaid());
    if(this->symbol!="ZAL")
    view->setCheckStoreUpdate(manager->getDocumentZALPolicy()->getDocumentZAL().getStoreResult());
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Order))
    view->getLineOrderSymbol()->setText(manager->getDocumentZALPolicy()->getDocumentZAL().getOrder());
    manager->getDocumentZALPolicy()->setPreviousZAL(manager->getDocumentZALPolicy()->getDocumentZAL().getPreviousDocumentsZAL());
    manager->getDocumentZALPolicy()->setPreviousZALVector(manager->getDocumentZALPolicy()->getDocumentZAL().getPreviousDocumentsZAL());
    view->getLineDocumentSymbol()->setEnabled(false);
    this->addToTable();

    if(symbol.contains("FV"))
        view->getComboBox()->setCurrentIndex(1);
    else
        view->getComboBox()->setCurrentIndex(0);

    manager->setDocumentPositions(manager->getDocumentZALPolicy()->getDocumentZAL().getDocumentPositions());

    addGood();
    addContractor();
    if(totalFromBase==true)
    {
              view->setAdvance(manager->getDocumentZALPolicy()->getDocumentZAL().getPaidValue());
              view->setLineGoodsValue(manager->getDocumentZALPolicy()->getDocumentZAL().getTotal());
              totalFromBase=false;
    }
    if (view->exec())
    {

        getDocumentData();
        if(isChangesOccured())
        {
        zalService->editDocumentZAL(manager->getDocumentZALPolicy()->getDocumentZAL());
        this->printDoc();
        return;
        }
     }
}

void DocumentZALController::getDocumentData()
{
     DocumentZAL documentZAL;
     documentZAL.setDocumentType(symbol);
     documentZAL.setSymbol(view->getLineDocumentSymbol()->text());
     MethodOfPayment mop;
     mop.setId((view->getWayToPay()->itemData(view->getWayToPay()->currentIndex()).toInt()));
     documentZAL.setMethodOfPayment(mop);
     documentZAL.setDocumentPlace(view->getLineDocumentPlace()->text());
     documentZAL.setDocumentDate(view->getDateIssue());
     documentZAL.setSaleDate(view->getSaleOrStoreDate());
     documentZAL.setPaymentDate(view->getPaymentDate()->date());
     documentZAL.setTotal(view->getLineGoodsValue());
     documentZAL.setPaidValue(view->getLineAdvance());
     documentZAL.setDiscount(view->getDiscountOrWaybillNo()->text().toDouble());
     if(ApplicationManager::getInstance()->containsModule(ModuleManager::Order))
     documentZAL.setOrder(view->getLineOrderSymbol()->text());
     documentZAL.setIssueName(view->getLineIssueName());
     documentZAL.setReceiveName(view->getLineReceiveName());
     documentZAL.setPaid(view->isPaid());
     if(this->symbol!="ZAL")
     documentZAL.setStoreResult(view->isStoreUpdating());
     else
     documentZAL.setStoreResult(false);
     documentZAL.setDocumentPositions(manager->getDocumentPosition());
     manager->getDocumentZALPolicy()->setDocumentData(documentZAL);
}

void DocumentZALController::insertOrderData(Order order)
{
    view->getLineOrderSymbol()->setText(order.getSymbol());
    view->setContractorData(order.getContractor());
    view->setLineIssueName(order.getIssueName());
    view->setLineReceiveName(order.getReceiveName());
    view->setLineDiscount(order.getDiscount());
    view->setLineDocumentPlace(order.getDocumentPlace());
    manager->setContractor(order.getContractor());
    manager->setDocumentPositions(order.getDocumentPositions());
    manager->countGoodsValue(view->getDiscountOrWaybillNo()->text().toDouble());
    setGoodsValue();
    addGood();
}

void DocumentZALController::updatePaymentDate()
{   view->getPaymentDate()->setDate(QDate::currentDate().addDays(
    mopModel->getMethodOfPayment(view->getWayToPay()->itemData(view->getWayToPay()->currentIndex()).toInt()).getMaturity()));
}

void  DocumentZALController:: fillBox(QComboBox *box,QVector<MethodOfPayment> values)
{
    for(int i = 0; i < values.size(); i++)
        box->addItem(values[i].getName(), QVariant::fromValue(values[i].getId()));
}

void DocumentZALController::printDoc()
{
     DocumentZAL doc = zalService->getDocumentZAL(view->getLineDocumentSymbol()->text());
     PrintSaleDocumentController *pc = new PrintSaleDocumentController(view->getLineDocumentSymbol()->text());
     pc->print(&doc);
     delete pc;
}
/**
  Demo blocker nr 1.
*/
void DocumentZALController::selectOrderOrFacture()
{
    manager->setTotal(0.0);
    manager->setTotalNet(0.0);
    manager->setTotalWithDiscount(0.0);
    manager->setDiscount(0.0);
    QString docTypeFilter = "ZK";
    SelectOrderController dialog(view,docTypeFilter);
    dialog.showDialog();

    Order order;

    if(dialog.getCancel() !=1)
    {
       order = dialog.addOrder();
       insertOrderData(order); //metoda z controllera
    }
}

void DocumentZALController::changedPaid()
{
 if(view->getPaymentDate()->date()<=view->getDateIssue())
    view->setCheckPaid(true);
 else
    view->setCheckPaid(false);
}

bool DocumentZALController::isChangesOccured() {
    return !(manager->getDocumentZALPolicy()->getOldDocumentZAL() == manager->getDocumentZALPolicy()->getDocumentZAL());
}

void DocumentZALController::selectZAL()
{
    QStringList docTypeFilter;
    docTypeFilter << "ZAL"; // faktury zaliczkowe
    SelectInvoiceController dialog(view, docTypeFilter);
    dialog.showDialog();
    qDebug()<<"";
    Document documentZAL;

    if(dialog.getCancel() !=1)
    {
       documentZAL = dialog.addInvoice();
       setPreviousZAL(documentZAL);
    }
}

void DocumentZALController::setPreviousZAL(Document documentZAL)
{
    SimpleDocumentInfo simple;
    simple.setSymbol(documentZAL.getSymbol());
    simple.setDocumentDate(documentZAL.getDocumentDate());
    simple.setTotal(documentZAL.getTotal());
    if(isOtherZal(simple))
    manager->getDocumentZALPolicy()->appendToPrevious(simple);
    manager->getDocumentZALPolicy()->setPreviousZAL(manager->getDocumentZALPolicy()->getPreviousZALVector());
    manager->countGoodsValue(view->getDiscountOrWaybillNo()->text().toDouble());
    setGoodsValue();
    addToTable();
}

bool DocumentZALController::isOtherZal(SimpleDocumentInfo simple)
{
    for(int i=0; i<manager->getDocumentZALPolicy()->getPreviousZALVector().size();i++)
    {
        if(manager->getDocumentZALPolicy()->getPreviousZALVector()[i].getSymbol()== simple.getSymbol())
            return false;
    }
    return true;
}

void DocumentZALController::addToTable()
{

    view->getZALTable()->setRowCount(manager->getDocumentZALPolicy()->getPreviousZAL().size());
    for (int i=0; i<manager->getDocumentZALPolicy()->getPreviousZAL().size(); i++)
    {
        insertZAL(i,0,new QTableWidgetItem(manager->getDocumentZALPolicy()->getPreviousZAL().value(i).getSymbol()));
        view->getZALTable()->item(i,0)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        insertZAL(i,1,new QTableWidgetItem(QVariant(manager->getDocumentZALPolicy()->getPreviousZAL().value(i).getDocumentDate()).toString()));
        view->getZALTable()->item(i,1)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        insertZAL(i,2,new QTableWidgetItem(QString::number(manager->getDocumentZALPolicy()->getPreviousZAL().value(i).getTotal(),',',2).replace(QRegExp("[.]"),",")));
        view->getZALTable()->item(i,2)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    }
}

void DocumentZALController::insertZAL(int i,int id, QTableWidgetItem *text)
{
    view->getZALTable()->setItem(i,id,text);
}

void DocumentZALController::removeZal()
{
    if (manager->getDocumentZALPolicy()->getPreviousZALVector().empty()!=true)
    {
    manager->getDocumentZALPolicy()->removeFromVector(view->getZALTable()->currentRow());
    view->getZALTable()->removeRow(view->getZALTable()->currentRow());
    manager->getDocumentZALPolicy()->setPreviousZAL(manager->getDocumentZALPolicy()->getPreviousZALVector());
    }
    manager->countGoodsValue(view->getDiscountOrWaybillNo()->text().toDouble());
    setGoodsValue();
}

void DocumentZALController::setGoodsValue()
{
    if(this->manager->getDocumentPosition().empty()==1)
    {
       manager->setTotal(0.0);
       manager->setTotalNet(0.0);
       manager->setTotalWithDiscount(0.0);
    }
 view->setLineGoodsValue(manager->getTotal());
 if(this->symbol == "RZL")
 {
 if(totalFromBase==false){
 view->setAdvance(manager->getAdvance());
 view->setLineGoodsValue(manager->getTotal());
 }
 }
 view->setLineGoodsValueDiscount(manager->getTotalWithDiscount());
 view->setLineGoodsValueNet(manager->getTotalNet());
}

void DocumentZALController::restoreTableState() {
    QByteArray state = tableStateManager->getState("ZAL_TABLE_GOODS");
    view->getGoodsTable()->horizontalHeader()->restoreState(state);
    QByteArray state2 = tableStateManager->getState("ZAL_TABLE_ZAL");
    view->getZALTable()->horizontalHeader()->restoreState(state2);
}

void DocumentZALController::saveTableState() {
    QByteArray state = view->getGoodsTable()->horizontalHeader()->saveState();
    QByteArray oldState = tableStateManager->getState("ZAL_TABLE_GOODS");
    if(state != oldState)
        tableStateManager->saveState("ZAL_TABLE_GOODS", state);

    QByteArray state2 = view->getZALTable()->horizontalHeader()->saveState();
    QByteArray oldState2 = tableStateManager->getState("ZAL_TABLE_ZAL");
    if(state2 != oldState2)
        tableStateManager->saveState("ZAL_TABLE_ZAL", state2);
}


