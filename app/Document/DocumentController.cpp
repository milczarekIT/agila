#include "DocumentController.h"

DocumentController::DocumentController()
{
    this->totalFromBase=false;
    tableStateManager = new TableStateManager();
    preferences = new SettingsPreferencesService();
    smodel = new SettingsModel();
}

DocumentController::~DocumentController()
{
    delete tableStateManager;
    delete smodel;
}

void DocumentController::selectContractor(){


    SelectContractorController dialog(view);

    if(this->symbol=="PZ"||this->symbol =="PW"||this->symbol =="RR"||this->symbol =="FZ"||this->symbol =="ZD")
        dialog.setContractorTypeFilter(Contractor::SUPPLIER);
    else if(this->symbol =="ZK")
        dialog.setContractorTypeFilter(Contractor::BUYER);

    dialog.showDialog();
    this->changingContractor=true;
    if(dialog.getCancel() !=1)
   {
       manager->setContractor(dialog.addContractor());
       addContractor();
   }
}

void DocumentController::addContractor()
{
    view->setContractorData(manager->getContractor());
    if(manager->getContractor().isCompany())
        view->setLineReceiveName(manager->getContractor().getRepresentative());
    else
    view->setLineReceiveName(manager->getContractor().getName());
    if (changingContractor==true)
    {
      view->setLineDiscount(manager->getContractor().getDiscount());
    }
    if(this->symbol=="PZ"||this->symbol=="WZ")
    {
        manager->countGoodsValue(0.0);
    }
    else
    {
        manager->countGoodsValue(view->getDiscountOrWaybillNo()->text().toDouble());
    }
    setGoodsValue();
}

void DocumentController::selectGoods()
{
   SelectGoodController dialog(view, symbol);
   if(symbol=="RR")
       dialog.setTaxForRRFilter(preferences->getTaxIdForRR());
   dialog.showDialog();

if(dialog.getView()->getGoodsTable()->getId()>0)
  {
    if(dialog.getCancel()!=1)
    {
         Goods good = dialog.addGood();
         DocumentPosition dp;

         dp.setGood(good);
         if(symbol!="PZ"&&symbol!="WZ"&&symbol!="RW"&&symbol!="PW"&&symbol!="MM")
         dp.setPriceLevel(dialog.getDialogQuantity()->getView()->getSelectedPriceLevel());
         else
         dp.setPriceLevel(Price::MAG);
         dp.setPriceNet(dialog.getDialogQuantity()->getView()->getPriceNet());

         if(dialog.getDialogQuantity()->getView()->isCheckQuantity())
         dp.setQuantity((dialog.getDialogQuantity()->getView()->getQuantity()));
         else
         dp.setQuantity(dialog.getDialogQuantity()->getView()->getMaxQuantity());

         dp.setTax(good.getTax());
         dp.setPriceGross(dialog.getDialogQuantity()->getView()->getPriceGross());
         manager->addGoodsToVector(dp);
         if(symbol!="PZ" && symbol!="WZ" && symbol!="RW" && symbol!="PW" && symbol!="MM")
         manager->countGoodsValue(view->getDiscountOrWaybillNo()->text().toDouble());
         else
         manager->countGoodsValue(0.0);
         addGood();
         setGoodsValue();

     }
   }
}


void DocumentController::insertGood(int i,int id, QTableWidgetItem *text)
{
    view->getGoodsTable()->setItem(i,id,text);
}

void DocumentController::editGood(int row, int column)
{
    if(isQuantityColumn(column))
    {
     double quantity = QVariant(view->getGoodsTable()->item(row,column)->text()).toDouble();
     manager->setChangedQuantity(row,quantity);
     if(symbol!="PZ"&&symbol!="WZ"&&symbol!="RW"&&symbol!="PW"&&symbol!="MM")
     manager->countGoodsValue(view->getDiscountOrWaybillNo()->text().toDouble());
     else
     manager->countGoodsValue(0.0);
     setGoodsValue();
     QString str;
     if(symbol!="FM")
     {
     view->getGoodsTable()->item(row,5)->setText(str.setNum(view->getGoodsTable()->item(row,column)->text().toDouble()*
                                                            view->getGoodsTable()->item(row,3)->text().toDouble(), ',', 2).replace(QRegExp("[.]"),","));
     }
     else
     {
         view->getGoodsTable()->item(row,3)->setText(str.setNum(view->getGoodsTable()->item(row,column)->text().toDouble()*
                                                                view->getGoodsTable()->item(row,2)->text().toDouble(), ',', 2).replace(QRegExp("[.]"),","));

     }

     }
 }

void DocumentController::removeGood(){
    if (!manager->getDocumentPosition().empty())
    {
        if(view->getGoodsTable()->currentRow()!=-1){

            manager->removeFromVector(view->getGoodsTable()->currentRow());
            view->getGoodsTable()->removeRow(view->getGoodsTable()->currentRow());
        }
        else
        {
            MessageBox *messageBox = new MessageBox();
            messageBox->createInfoBox("Zaznacz pozycje do usunięcia!");
        }
        if(symbol!="PZ"&&symbol!="WZ"&&symbol!="RW"&&symbol!="PW"&&symbol!="MM")
            manager->countGoodsValue(view->getDiscountOrWaybillNo()->text().toDouble());
        else
            manager->countGoodsValue(0.0);
        setGoodsValue();
    }
}

void DocumentController::checkChanges()
{
    if(validator->isEmptyForm())
        view->reject();

   else if(isChangesOccured())
    {
        MessageBox *messageBox = new MessageBox();
        if (messageBox->createQuestionBox("Dokonano zmian") == MessageBox::YES)
           {
               validator->validateDocForm(edition);
           }
        else
            view->reject(); // zmiany dokonane, ale użytkowik chce anulować
    }
    else
         view->reject(); // nie dokonano zmian, anuluj
}



void DocumentController::checkRequiredFields()
{
    if(validator->isEmptyForm())
    {
        MessageBox *messageBox = new MessageBox();
        messageBox->createInfoBox("Uzupełnij formularz!");
    }
    else
   validator->validateDocForm(edition);
}

void DocumentController::discountChanged(){

   manager->countGoodsValue(view->getDiscountOrWaybillNo()->text().toDouble());
   setGoodsValue();
}

DocumentManager* DocumentController::getDocumentManager()
{
    return this->manager;
}

QString DocumentController::getSymbol()
{
return this->symbol;
}


bool DocumentController::getEdition()
{
    return this->edition;
}

void DocumentController::selectOrderOrFacture(){}
void DocumentController::selectZAL(){}
void DocumentController::changedPaid(){}
void DocumentController::updatePaymentDate(){}
void DocumentController::changedRealizedOrSymbol(){}
void DocumentController::removeZal(){}
