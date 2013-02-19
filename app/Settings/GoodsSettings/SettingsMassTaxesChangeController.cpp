#include "SettingsMassTaxesChangeController.h"

SettingsMassTaxesChangeController::SettingsMassTaxesChangeController(QObject *parent) :
    SettingsAbstractItemController(parent)
{
    view = new SettingsMassTaxesChangeView(this);
    goodsGroupModel = new GoodsGroupModel();
    taxChangerModel = new TaxChangerModel();
    taxModel = new TaxModel();
    setModel();
}

void SettingsMassTaxesChangeController::setModel()
{
    basePrice = Price::NET;
    view->getGoodGroup()->addItem("WSZYSTKIE");
    fillBox(view->getGoodGroup(),goodsGroupModel->getGoodsGroups());
    fillBox(view->getActualTax(),taxModel->getTaxes(true));
    fillBox(view->getNewTax(),taxModel->getTaxes(true));
}

void SettingsMassTaxesChangeController::fillBox(QComboBox *box,QVector<GoodsGroup> values)
{
    box->clear();
    for(int i = 0; i < values.size(); i++)
        box->addItem(values[i].getName(), QVariant::fromValue(values[i].getId()));
}

void SettingsMassTaxesChangeController::fillBox(QComboBox *box,QVector<Tax> values)
{
    box->clear();
    for(int i = 0; i < values.size(); i++)
        box->addItem(values[i].getName(), QVariant::fromValue(values[i].getId()));
}

void SettingsMassTaxesChangeController::chooseKindOfCount()
{
    if (view->getRadioGross()->isChecked())
    {
        view->getLabel()->setText("netto.");
        basePrice = Price::GROSS;
    }
    else
    {
        view->getLabel()->setText("brutto.");
        basePrice = Price::NET;
    }
}

void SettingsMassTaxesChangeController::saveChanges()
{
    int priceType;
    QString value = view->getPriceType()->currentText();

    if (value == "ABC") priceType = Price::ABC;
    else if (value == "MAG") priceType = Price::MAG;
    else if (value == "ABC i MAG") priceType = Price::ABC + Price::MAG;



    if (view->getMessageBox()->createQuestionBox("Masowa zmiana stawek VAT w produktach!") == MessageBox::YES)
    {
        Tax oldTax = taxModel->getTax(view->getActualTax()->itemData(view->getActualTax()->currentIndex()).toInt());
        Tax newTax = taxModel->getTax(view->getNewTax()->itemData(view->getNewTax()->currentIndex()).toInt());

        if(view->getGoodGroup()->currentText() == "WSZYSTKIE")
        {
            taxChangerModel->changeTaxesForAll(oldTax,newTax,basePrice,priceType);
        }
        else
        {
            taxChangerModel->changeTaxesForGroup(view->getGoodGroup()->itemData(view->getGoodGroup()->currentIndex()).toInt(),
                                                                                newTax,basePrice,priceType);
        }
        view->emitChangesWereMade();
    }
}

SettingsMassTaxesChangeView *SettingsMassTaxesChangeController::getView() {return view;}

