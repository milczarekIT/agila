#include "DocumentFKController.h"

DocumentFKController::DocumentFKController(QWidget* parent,bool edit) {
    this->edition = edit;
    this->symbol = "FK";
    this->view = new DocumentFKView(parent,this);
    this->invoiceService = new InvoiceService();
    this->fkService = new DocumentFKService();
    this->smodel = new SettingsModel();
    this->mopModel = new MOPModel();
    this->validator = new DocumentValidator(view,symbol);
    this->managerFK = new DocumentFKManager();
    this->tableStateManager = new TableStateManager();
    fillBox(view->getBoxWayToPay(),mopModel->getMethodsOfPayment());
    first=false;
    totalFromBase=false;
    restoreTableState();
}
DocumentFKController::DocumentFKController(){}

DocumentFKController::~DocumentFKController()
{
    if(symbol=="FK")
    delete fkService;
    saveTableState();
    delete invoiceService;
    delete smodel;
    delete mopModel;
    delete validator;
    delete managerFK;
    delete tableStateManager;
}

void DocumentFKController::exec()
{
    dnc = new DocumentNumeratorController("FK");
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
        fkService->addDocumentFK(managerFK->getFKPolicy()->getFK());
        this->printDoc();
        return;
    }
    return;
}



void DocumentFKController::exec(QString symbol)
{
    this->first = true;
    this->totalFromBase=true;

    managerFK->getFKPolicy()->setFK(fkService->getDocumentFK(symbol));
    managerFK->getFKPolicy()->setInvoice(managerFK->getFKPolicy()->getFK().getInvoice());
    managerFK->getFKPolicy()->setFKOld(managerFK->getFKPolicy()->getFK());
    view->setLineDocumentSymbol(managerFK->getFKPolicy()->getFK().getSymbol());
    view->setContractorDataOld(managerFK->getFKPolicy()->getFK().getInvoice().getContractor());
    managerFK->getFKPolicy()->setContractor(managerFK->getFKPolicy()->getFK().getContractor());
    view->setContractorDataNew(managerFK->getFKPolicy()->getContractor());
    view->setDateEditInvoiceDate(managerFK->getFKPolicy()->getFK().getInvoice().getDocumentDate());
    view->setRealatedTo(managerFK->getFKPolicy()->getFK().getInvoice().getSymbol());
    view->getBoxWayToPay()->setCurrentIndex(view->getBoxWayToPay()->findData(QVariant::fromValue(managerFK->getFKPolicy()->getFK().getMethodOfPayment().getId())));
    view->setLineDocumentPlace(managerFK->getFKPolicy()->getFK().getDocumentPlace());
    view->setDateIssue(managerFK->getFKPolicy()->getFK().getDocumentDate());
    view->setSaleDate(managerFK->getFKPolicy()->getFK().getSaleDate());
    view->setPaymentDate(managerFK->getFKPolicy()->getFK().getPaymentDate());
    view->setLineDiscountNew(managerFK->getFKPolicy()->getFK().getDiscount());
    view->setLineDiscount(managerFK->getFKPolicy()->getFK().getInvoice().getDiscount());
    view->setLineIssueName(managerFK->getFKPolicy()->getFK().getIssueName());
    view->setLineReceiveName(managerFK->getFKPolicy()->getFK().getReceiveName());
    view->setCheckPaid(managerFK->getFKPolicy()->getFK().isPaid());
    view->setCheckStoreUpdate(managerFK->getFKPolicy()->getFK().getStoreResult());
    managerFK->setDocumentPositions(managerFK->getFKPolicy()->getFK().getDocumentPositions());
    managerFK->setDocumentPositionsOld(managerFK->getFKPolicy()->getFK().getInvoice().getDocumentPositions());
    managerFK->countGoodsValue(view->getLineDiscount()->text().toDouble(),first);
    view->getLineDocumentSymbol()->setEnabled(false);
    setGoodsValue();
    addGood();
    if(totalFromBase==true)
    {
    view->setLineToPayAfterCorrection(managerFK->getFKPolicy()->getFK().getTotal());
    totalFromBase=false;
    }
    if (view->exec())
    {
        getDocumentData();
        if(isChangesOccured())
        {
        fkService->editDocumentFK(managerFK->getFKPolicy()->getFK());
        this->printDoc();
    }
        return;
     }
    return;
}

void DocumentFKController::getDocumentData()
{
    DocumentFK fk;
    fk.setSymbol(view->getLineDocumentSymbol()->text());

    MethodOfPayment mop;
    mop.setId((view->getBoxWayToPay()->itemData(view->getBoxWayToPay()->currentIndex()).toInt()));
    fk.setMethodOfPayment(mop);
    fk.setDocumentPlace(view->getLineDocumentPlace()->text());
    fk.setDocumentDate(view->getDateIssue());
    fk.setSaleDate(view->getSaleDate());
    fk.setPaymentDate(view->getPaymentDate());
    fk.setTotal(view->getLineToPayAfterCorrection());
    fk.setDiscount(view->getLineDiscountNew()->text().toDouble());
    fk.setReceiveName(view->getLineReceiveName());
    fk.setOrder();
    fk.setIssueName(view->getLineIssueName());
    fk.setPaid(view->isPaid());
    fk.setStoreResult(view->isStoreUpdating());
    if (managerFK->getDocumentPositionNew().empty()==1)
      fk.setDocumentPositions(managerFK->getDocumentPositionOld());
     else
      fk.setDocumentPositions(managerFK->getDocumentPositionNew());
   managerFK->getFKPolicy()->setFactureData(fk);
}

void DocumentFKController::selectGoods()
{
   SelectGoodController dialog(view,"FK");
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

         dp.setTax(good.getTax());
         dp.setPriceGross(dialog.getDialogQuantity()->getView()->getPriceGross());
         managerFK->addGoodsToVector(dp);
         managerFK->countGoodsValue(view->getLineDiscount()->text().toDouble(),first);
         setGoodsValue();
         addGood();
     }
   }
}

void DocumentFKController::editGood(int row, int column)
{
    if(isQuantityColumn(column))
    {
     double quantity = QVariant(view->getGoodsTableNew()->item(row,column)->text()).toDouble();
     managerFK->setChangedQuantity(row,quantity);
     managerFK->countGoodsValue(view->getLineDiscountNew()->text().toDouble(),first);
     setGoodsValue();
     QString str;
     view->getGoodsTableNew()->item(row,5)->setText(str.setNum(view->getGoodsTableNew()->item(row,column)->text().toDouble()*
                                                            view->getGoodsTableNew()->item(row,3)->text().toDouble(), ',', 2).replace(QRegExp("[.]"),","));

    }
 }

bool DocumentFKController::isQuantityColumn(int column)
{
    if (column==4)
        return true;
    else
        return false;
}

void DocumentFKController::discountChanged(){

   managerFK->countGoodsValue(view->getLineDiscountNew()->text().toDouble(),first);
   setGoodsValue();
}


void DocumentFKController::removeGood(){
    if (managerFK->getDocumentPositionNew().empty()!=true)
    {
    managerFK->removeFromVector(view->getGoodsTableNew()->currentRow());
    view->getGoodsTableNew()->removeRow(view->getGoodsTableNew()->currentRow());
    }
managerFK->countGoodsValue(view->getLineDiscountNew()->text().toDouble(),first);
setGoodsValue();
}

void DocumentFKController::selectContractor(){

    SelectContractorController dialog(view);
    dialog.showDialog();
    if(dialog.getCancel() !=1)
   {
       Contractor c =dialog.addContractor();
       if(c.isCompany())
           view->setLineReceiveName(c.getRepresentative());
       else
       view->setLineReceiveName(c.getName());
       view->setContractorDataNew(c);
       if(!view->getContractorDataNew()->toPlainText().isEmpty() && symbol == "FK")
           managerFK->getFKPolicy()->setContractor(c);
       else if(!view->getContractorDataNew()->toPlainText().isEmpty() && symbol == "FZK")
           managerFK->getFZKPolicy()->setContractor(c);
   }
}


void DocumentFKController::selectInvoice()
{   setFirst(true);
    QStringList docTypeFilter;
    docTypeFilter << "FMP" << "FV" << "PRO"; // faktura VAT, VAT-MP, PROFORMA
    SelectInvoiceController dialog(view, docTypeFilter);
    dialog.showDialog();

    Document invoice;

    if(dialog.getCancel() !=1)
    {
       invoice = dialog.addInvoice();
       insertInvoiceData(invoice);
    }
}

bool DocumentFKController::isChangesOccured() {

    return !(managerFK->getFKPolicy()->getFKOld() == managerFK->getFKPolicy()->getFK());
}

void DocumentFKController::checkChanges()
{
    getDocumentData();
    if(validator->isEmptyFormFK())
       view->reject();
    else if(isChangesOccured())
    {
        MessageBox *messageBox = new MessageBox();
        if (messageBox->createQuestionBox("Dokonano zmian") == MessageBox::YES)
           this->checkRequredFields();
        else
            view->reject(); // zmiany dokonane, ale użytkowik chce anulować
    }
    else
         view->reject(); // nie dokonano zmian, anuluj
}

void DocumentFKController::addGood()
{
   view->getGoodsTableOld()->setRowCount(managerFK->getDocumentPositionOld().size());
   if(first==true)
   {
    for (int i=0; i<managerFK->getDocumentPositionOld().size(); i++)
     {
       insertGood(i,0,new QTableWidgetItem(managerFK->getDocumentPositionOld().value(i).getGood().getName()));
       insertGood(i,1,new QTableWidgetItem(managerFK->getDocumentPositionOld().value(i).getGood().getSymbol()));
       insertGood(i,2,new QTableWidgetItem(QString::number(managerFK->getDocumentPositionOld().value(i).getPriceNet(),',',2).replace(QRegExp("[.]"),",")));
       insertGood(i,3,new QTableWidgetItem(QString::number(managerFK->getDocumentPositionOld().value(i).getPriceGross(),',',2).replace(QRegExp("[.]"),",")));
       insertGood(i,5,new QTableWidgetItem(QString::number(managerFK->getDocumentPositionOld().value(i).getPriceGross()*
                                                           managerFK->getDocumentPositionOld().value(i).getQuantity(), ',', 2).replace(QRegExp("[.]"),",")));
       insertGood(i,4,new QTableWidgetItem(QString::number(managerFK->getDocumentPositionOld().value(i).getQuantity(),',',
                                                           managerFK->getDocumentPositionOld().value(i).getGood().getUnit().getZeroPlaces()).replace(QRegExp("[.]"),",")));

    } this->first=false;
   }
view->getGoodsTableNew()->setRowCount(managerFK->getDocumentPositionNew().size());
for (int i=0; i<managerFK->getDocumentPositionNew().size(); i++)
 {
       insertGood(i,0,new QTableWidgetItem(managerFK->getDocumentPositionNew().value(i).getGood().getName()));
       view->getGoodsTableNew()->item(i,0)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
       insertGood(i,1,new QTableWidgetItem(managerFK->getDocumentPositionNew().value(i).getGood().getSymbol()));
       view->getGoodsTableNew()->item(i,1)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
       insertGood(i,2,new QTableWidgetItem(QString::number(managerFK->getDocumentPositionNew().value(i).getPriceNet(),',',2).replace(QRegExp("[.]"),",")));
       view->getGoodsTableNew()->item(i,2)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
       insertGood(i,3,new QTableWidgetItem(QString::number(managerFK->getDocumentPositionNew().value(i).getPriceGross(),',',2).replace(QRegExp("[.]"),",")));
       view->getGoodsTableNew()->item(i,3)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
       insertGood(i,5,new QTableWidgetItem(QString::number(managerFK->getDocumentPositionNew().value(i).getPriceGross()*
                                                           managerFK->getDocumentPositionNew().value(i).getQuantity(), ',', 2).replace(QRegExp("[.]"),",")));
       view->getGoodsTableNew()->item(i,5)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
       insertGood(i,4,new QTableWidgetItem(QString::number(managerFK->getDocumentPositionNew().value(i).getQuantity(),',',
                                                           managerFK->getDocumentPositionNew().value(i).getGood().getUnit().getZeroPlaces()).replace(QRegExp("[.]"),",")));

    }
}

void DocumentFKController::insertGood(int i,int id, QTableWidgetItem *text)
{
    if (first==true)
    view->getGoodsTableOld()->setItem(i,id,text);
    else
    view->getGoodsTableNew()->setItem(i,id,text);
}

void DocumentFKController::setGoodsValue()
{
    if(this->managerFK->getDocumentPositionNew().empty()==1)
    {
       managerFK->setTotalWithDiscountNew(0.0);
       managerFK->setTotalNew(0.0);
       managerFK->setTotalNetNew(0.0);
       managerFK->setToPay(0.0);
    }
    if(first==true)
    {
 view->setLineGoodsValue(managerFK->getTotal());
 view->setLineGoodsValueDiscount(managerFK->getTotalWithDiscount());
 view->setLineGoodsValueNet(managerFK->getTotalNet());
    }

    if(totalFromBase==false)
 view->setLineToPayAfterCorrection(managerFK->getToPay());
 view->setLineGoodsValueNew(managerFK->getTotalNew());
 view->setLineGoodsValueDiscountNew(managerFK->getTotalWithDiscountNew());
 view->setLineGoodsValueNetNew(managerFK->getTotalNetNew());
}

void DocumentFKController::insertInvoiceData(Document invoice)
{
    managerFK->getFKPolicy()->setInvoice(invoiceService->getInvoice(invoice.getSymbol()));
    view->setRealatedTo(invoice.getSymbol());
    view->setDateEditInvoiceDate(invoice.getDocumentDate());
    view->setContractorDataOld(invoice.getContractor());
    view->setContractorDataNew(invoice.getContractor());
    view->getBoxWayToPay()->setCurrentIndex(view->getBoxWayToPay()->findData(QVariant::fromValue(managerFK->getFKPolicy()->getInvoice().getMethodOfPayment().getId())));
    view->setSaleDate(managerFK->getFKPolicy()->getInvoice().getSaleDate());
    view->setPaymentDate(managerFK->getFKPolicy()->getInvoice().getPaymentDate());
    view->setCheckPaid(managerFK->getFKPolicy()->getInvoice().isPaid());
    view->setCheckStoreUpdate(managerFK->getFKPolicy()->getInvoice().getStoreResult());
    view->setLineIssueName(invoice.getIssueName());
    view->setLineReceiveName(invoice.getReceiveName());
    view->setLineDiscount(managerFK->getFKPolicy()->getInvoice().getDiscount());
    view->setLineDiscountNew(managerFK->getFKPolicy()->getInvoice().getDiscount());
    managerFK->getFKPolicy()->setContractor(invoice.getContractor());
    managerFK->setDocumentPositions(managerFK->getFKPolicy()->getInvoice().getDocumentPositions());
    managerFK->setDocumentPositionsOld(managerFK->getFKPolicy()->getInvoice().getDocumentPositions());
    managerFK->countGoodsValue(view->getLineDiscount()->text().toDouble(),first);
    setGoodsValue();
    addGood();
}

void DocumentFKController::updatePaymentDate()
{   view->paymentDate->setDate(QDate::currentDate().addDays(
    mopModel->getMethodOfPayment(view->getBoxWayToPay()->itemData(view->getBoxWayToPay()->currentIndex()).toInt()).getMaturity()));
}

void DocumentFKController::checkRequredFields()
{
    this->validator->validateDocFormFK(edition);

}

void DocumentFKController::printDoc()
{
    PrintSaleDocumentController *pc = new PrintSaleDocumentController(view->getLineDocumentSymbol()->text());
    DocumentFK doc = fkService->getDocumentFK(view->getLineDocumentSymbol()->text());
    pc->print(&doc);
    delete pc;
}

DocumentFKView *DocumentFKController::getView(){
return this->view;
}

bool DocumentFKController::getEdition(){
    return this->edition;
}

void  DocumentFKController:: fillBox(QComboBox *box,QVector<MethodOfPayment> values)
{
    for(int i = 0; i < values.size(); i++)
        box->addItem(values[i].getName(), QVariant::fromValue(values[i].getId()));
}

DocumentFKManager *DocumentFKController::getManager()
{
    return this->managerFK;
}
bool DocumentFKController::getFirst()
{
    return this->first;
}
void DocumentFKController::setFirst(bool first)
{
    this->first=first;
}
QString DocumentFKController::getSymbol()
{
    return this->symbol;
}
void DocumentFKController::restoreTableState() {
    QByteArray state = tableStateManager->getState("DOCUMENT_FK_TABLE_GOODS");
    view->getGoodsTableNew()->horizontalHeader()->restoreState(state);
    view->getGoodsTableOld()->horizontalHeader()->restoreState(state);
}

void DocumentFKController::saveTableState() {
    QByteArray state = view->getGoodsTableNew()->horizontalHeader()->saveState();
    QByteArray oldState = tableStateManager->getState("DOCUMENT_FK_TABLE_GOODS");
    if(state != oldState)
        tableStateManager->saveState("DOCUMENT_FK_TABLE_GOODS", state);
}
