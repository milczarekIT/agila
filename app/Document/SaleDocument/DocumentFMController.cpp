#include "DocumentFMController.h"

DocumentFMController::DocumentFMController(QWidget* parent, QString symbol, bool edit) {
    this->edition = edit;
    this->symbol = symbol;
    this->view = new DocumentFMView(parent,this);
    this->invoiceService = new InvoiceService();
    this->validator = new DocumentValidator(view,symbol);
    this->manager= new DocumentFMManager();
    this->mopModel = new MOPModel();
    fillBox(view->getWayToPay(),mopModel->getMethodsOfPayment());
    changingContractor=false;
    restoreTableState();
}

DocumentFMController::~DocumentFMController()
{
    saveTableState();
    delete invoiceService;
    delete validator;
    delete manager;
    delete mopModel;
}

void DocumentFMController::exec()
{
    dnc = new DocumentNumeratorController(symbol);
    QString nextSymbol = dnc->getNextSymbol();
    view->getLineDocumentSymbol()->setText(nextSymbol);
    delete dnc;
    dnc = NULL;

    QString documentPlace = smodel->getDefualtDocumentPlace().getName();
    this->view->setLineDocumentPlace(documentPlace);

    this->view->setLineIssueName(ApplicationManager::getInstance()->getLoggedUser().getName()); //TODO dane użytkownika programu!!!!!!!!!!!!!!!!!

    if (view->exec())
    {
        getDocumentData();
        invoiceService->addInvoice(manager->getInvoicePolicy()->getInvoice());
        this->printDoc();
        return;
    }
    return;
}

void DocumentFMController::exec(QString Symbol)
{
    this->edition = true;
    this->totalFromBase=true;
    manager->getInvoicePolicy()->setInvoice(invoiceService->getInvoice(Symbol));
    manager->getInvoicePolicy()->setOldInvoice(manager->getInvoicePolicy()->getInvoice());
    view->setLineDocumentSymbol(manager->getInvoicePolicy()->getInvoice().getSymbol());
    manager->setContractor(manager->getInvoicePolicy()->getInvoice().getContractor());
    view->getWayToPay()->setCurrentIndex(view->getWayToPay()->findData(QVariant::fromValue(manager->getInvoicePolicy()->getInvoice().getMethodOfPayment().getId())));
    view->setLineDocumentPlace(manager->getInvoicePolicy()->getInvoice().getDocumentPlace());
    view->setDateIssue(manager->getInvoicePolicy()->getInvoice().getDocumentDate());
    view->setSaleOrStoreDate(manager->getInvoicePolicy()->getInvoice().getSaleDate());
    view->setPaymentDate(manager->getInvoicePolicy()->getInvoice().getPaymentDate());
    view->setLineDiscount(manager->getInvoicePolicy()->getInvoice().getDiscount());
    view->setLineIssueName(manager->getInvoicePolicy()->getInvoice().getIssueName());
    view->setLineReceiveName(manager->getInvoicePolicy()->getInvoice().getReceiveName());
    view->setCheckPaid(manager->getInvoicePolicy()->getInvoice().isPaid());
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Order))
    view->getLineOrderSymbol()->setText(manager->getInvoicePolicy()->getInvoice().getOrder());
    view->setCheckStoreUpdate(manager->getInvoicePolicy()->getInvoice().getStoreResult());
    manager->setDocumentPositions(manager->getInvoicePolicy()->getInvoice().getDocumentPositions());
    view->getLineDocumentSymbol()->setEnabled(false);
    addGood();
    addContractor();
    if(totalFromBase==true)
    {
    view->setLineGoodsValueDiscount(manager->getInvoicePolicy()->getInvoice().getTotal());
    totalFromBase=false;
    }
    if (view->exec())
    {
        getDocumentData();
        if(isChangesOccured())
        {
        invoiceService->editInvoice(manager->getInvoicePolicy()->getInvoice());
        this->printDoc();
       }
    }
}

void DocumentFMController::getDocumentData()
{
     Invoice invoice;
     invoice.setDocumentType(symbol);
     invoice.setSymbol(view->getLineDocumentSymbol()->text());
     MethodOfPayment mop;
     mop.setId((view->getWayToPay()->itemData(view->getWayToPay()->currentIndex()).toInt()));
     invoice.setMethodOfPayment(mop);
     invoice.setDocumentPlace(view->getLineDocumentPlace()->text());
     invoice.setDocumentDate(view->getDateIssue());
     invoice.setSaleDate(view->getSaleOrStoreDate());
     invoice.setPaymentDate(view->getPaymentDate()->date());
     invoice.setTotal(view->getLineGoodsValueDiscount());
     invoice.setDiscount(view->getDiscountOrWaybillNo()->text().toDouble());
     if(ApplicationManager::getInstance()->containsModule(ModuleManager::Order))
     invoice.setOrder(view->getLineOrderSymbol()->text());
     invoice.setIssueName(view->getLineIssueName());
     invoice.setReceiveName(view->getLineReceiveName());
     invoice.setPaid(view->isPaid());
     invoice.setStoreResult(view->isStoreUpdating());
     invoice.setDocumentPositions(manager->getDocumentPosition());
     manager->getInvoicePolicy()->setDocumentData(invoice);
}

void DocumentFMController::selectGoods()
{

   SelectGoodController dialog(view,symbol);
   dialog.showDialog();
  if(dialog.getView()->getGoodsTable()->getId()>0)
  {
    if(dialog.getCancel()!=1)
    {
         Goods good = dialog.addGood();
         DocumentPosition dp;
         dp.setGood(good); 
         dp.setPriceLevel(dialog.getDialogQuantity()->getView()->getSelectedPriceLevel());
         dp.setPriceNet((dialog.getDialogQuantity()->getView()->getPriceNet()));

         if(dialog.getDialogQuantity()->getView()->isCheckQuantity())
         dp.setQuantity((dialog.getDialogQuantity()->getView()->getQuantity()));
         else
         dp.setQuantity(dialog.getDialogQuantity()->getView()->getMaxQuantity());
         dp.setTax(good.getTax()); //podatek potrzebny azeby obliczyc marze netto przy drukowaniu
         dp.setPriceGross(good.getPriceNet(Price::MAG).value());//wczytuje cene zakupu potrzebna do wyliczenia marzy

         manager->addGoodsToVector(dp);
         manager->countGoodsValue(view->getDiscountOrWaybillNo()->text().toDouble());
         setGoodsValue();
         addGood();
     }
   }
}

void DocumentFMController::addGood()
{
   view->getGoodsTable()->setRowCount(manager->getDocumentPosition().size());
   for (int i=0; i<manager->getDocumentPosition().size(); i++)
   {
       insertGood(i,0,new QTableWidgetItem(manager->getDocumentPosition().value(i).getGood().getName()));
       view->getGoodsTable()->item(i,0)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
       insertGood(i,2,new QTableWidgetItem(QString::number(manager->getDocumentPosition().value(i).getPriceNet(),',',2).replace(QRegExp("[.]"),",")));
       view->getGoodsTable()->item(i,2)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
       insertGood(i,3,new QTableWidgetItem(QString::number(manager->getDocumentPosition().value(i).getPriceNet()*
                                                           manager->getDocumentPosition().value(i).getQuantity(), ',', 2).replace(QRegExp("[.]"),",")));
       view->getGoodsTable()->item(i,3)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
       insertGood(i,1,new QTableWidgetItem(QString::number(manager->getDocumentPosition().value(i).getQuantity(),',',
                                                           manager->getDocumentPosition().value(i).getGood().getUnit().getZeroPlaces()).replace(".", ",")));

   }
}

void DocumentFMController::setGoodsValue()
{
    if(manager->getDocumentPosition().empty()==1)
    {
       manager->setTotalWithDiscount(0.0);
       manager->setTotal(0.0);
    }
 view->setLineGoodsValue(manager->getTotal());
 if(totalFromBase==false)
 view->setLineGoodsValueDiscount(manager->getTotalWithDiscount());
}


bool DocumentFMController::isQuantityColumn(int column)
{
    if (column==1)
        return true;
    else
        return false;
}

void DocumentFMController::insertOrderData(Order order)
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

void DocumentFMController::updatePaymentDate()
{
    view->getPaymentDate()->setDate(QDate::currentDate().addDays(
    mopModel->getMethodOfPayment(view->getWayToPay()->itemData(view->getWayToPay()->currentIndex()).toInt()).getMaturity()));
}

void  DocumentFMController:: fillBox(QComboBox *box,QVector<MethodOfPayment> values)
{
    for(int i = 0; i < values.size(); i++)
        box->addItem(values[i].getName(), QVariant::fromValue(values[i].getId()));
}

void DocumentFMController::printDoc()
{
        PrintSaleDocumentController *pc = new PrintSaleDocumentController(view->getLineDocumentSymbol()->text());
        Invoice doc = invoiceService->getInvoice(view->getLineDocumentSymbol()->text());
        pc->print(&doc);
        delete pc;
}

void DocumentFMController::selectOrderOrFacture()
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

void DocumentFMController::changedPaid()
{
 if(view->getPaymentDate()->date()<=view->getDateIssue())
    view->setCheckPaid(true);
 else
    view->setCheckPaid(false);
}

bool DocumentFMController::isChangesOccured() {
    return !(manager->getInvoicePolicy()->getOldInvoice() == manager->getInvoicePolicy()->getInvoice());
}

void DocumentFMController::restoreTableState() {
    QByteArray state = tableStateManager->getState("DOCUMENT_FM_TABLE_GOODS");
    view->getGoodsTable()->horizontalHeader()->restoreState(state);
}

void DocumentFMController::saveTableState() {
    QByteArray state = view->getGoodsTable()->horizontalHeader()->saveState();
    QByteArray oldState = tableStateManager->getState("DOCUMENT_FM_TABLE_GOODS");
    if(state != oldState)
        tableStateManager->saveState("DOCUMENT_FM_TABLE_GOODS", state);
}
