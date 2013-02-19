#include "SettingsMassTaxesChangeView.h"

SettingsMassTaxesChangeView::SettingsMassTaxesChangeView(SettingsMassTaxesChangeController *controller, QWidget *parent) :
        SettingsAbstractItemView(parent)
{
    this->controller = controller;
    initGraphicElements();
    setGraphicSettings();
    setInterfaceController();
}

void SettingsMassTaxesChangeView::initGraphicElements()
{
    mainLayout->addWidget(new QLabel("Masowa zmiana stawek VAT: "),1,1,1,7);
    mainLayout->addWidget(new QLabel("Oblicz cenę "),3,1,1,1);
    mainLayout->addWidget(radioNet = new QRadioButton("netto"),3,2,1,1);
    mainLayout->addWidget(radioGross = new QRadioButton("brutto"),3,3,1,1);
    mainLayout->addWidget(new QLabel("na podstawie ceny "),3,4,1,1);
    mainLayout->addWidget(label = new QLabel("brutto."),3,5,1,1);
    mainLayout->addWidget(new QLabel("Aktualna stawka VAT: "),5,2,1,2);
    mainLayout->addWidget(new QLabel("Nowa stawka VAT: "),6,2,1,2);
    mainLayout->addWidget(new QLabel("Grupa dóbr: "),7,2,1,2);
    mainLayout->addWidget(new QLabel("Typy cen: "),8,2,1,2);
    mainLayout->addWidget(actualTax = new QComboBox,5,4,1,4);
    mainLayout->addWidget(newTax = new QComboBox,6,4,1,4);
    mainLayout->addWidget(goodGroup = new QComboBox,7,4,1,4);
    mainLayout->addWidget(priceType = new QComboBox,8,4,1,3);
    mainLayout->addWidget(pushSave = new Button(ButtonStruct("Zapisz","Zapisywanie dokonanych zmian", QSize(100,25))),8,7,1,1,Qt::AlignRight);
    mainLayout->addItem(new QSpacerItem(0,50,QSizePolicy::Maximum, QSizePolicy::Expanding),9,0,1,10);
    fillPriceTypeBox();
}

void SettingsMassTaxesChangeView::setGraphicSettings()
{
    mainLayout->setColumnMinimumWidth(5,50);
    mainLayout->setColumnMinimumWidth(6,60);
    mainLayout->setColumnMinimumWidth(9,60);
    mainLayout->setRowMinimumHeight(0,25);
    mainLayout->setRowMinimumHeight(2,30);
    mainLayout->setRowMinimumHeight(4,30);
    mainLayout->setRowMinimumHeight(8,10);
    radioNet->setChecked(true);
}

void SettingsMassTaxesChangeView::fillPriceTypeBox()
{
    priceType->addItem("ABC");
    priceType->addItem("MAG");
    priceType->addItem("ABC i MAG");

}

void SettingsMassTaxesChangeView::setInterfaceController()
{
    connect(radioNet,SIGNAL(clicked()),controller,SLOT(chooseKindOfCount()));
    connect(radioGross,SIGNAL(clicked()),controller,SLOT(chooseKindOfCount()));
    connect(pushSave,SIGNAL(clicked()),controller,SLOT(saveChanges()));
}

QRadioButton *SettingsMassTaxesChangeView::getRadioNet() {return radioNet; }
QRadioButton *SettingsMassTaxesChangeView::getRadioGross() {return radioGross; }
QLabel *SettingsMassTaxesChangeView::getLabel() {return label; }
QComboBox *SettingsMassTaxesChangeView::getActualTax() {return actualTax; }
QComboBox *SettingsMassTaxesChangeView::getNewTax() {return newTax; }
QComboBox *SettingsMassTaxesChangeView::getGoodGroup() {return goodGroup; }
Button *SettingsMassTaxesChangeView::getPushSave() {return pushSave; }
QComboBox *SettingsMassTaxesChangeView::getPriceType() {return priceType;}

