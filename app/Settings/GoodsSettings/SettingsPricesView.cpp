#include "SettingsPricesView.h"

SettingsPricesView::SettingsPricesView(SettingsPricesController *controller,QWidget *parent) :
    SettingsAbstractItemView(parent)
{
    this->controller=controller;
    initGraphicElements();
    setGraphicSettings();
    setInterfaceController();
}
SettingsPricesView::~SettingsPricesView()
{
}

void SettingsPricesView::initGraphicElements()
{
    mainLayout->addWidget(new QLabel("Zdefiniuj domyślny narzut, upust cen:"),1,1,1,4);
    mainLayout->addWidget(new QLabel("Narzut ceny A: "),3,2,1,1);
    mainLayout->addWidget(lineMarginA = new QLineEdit(),3,3,1,1);
    mainLayout->addWidget(new QLabel("Upust ceny B: "),4,2,1,1);
    mainLayout->addWidget(lineDiscountB = new QLineEdit(),4,3,1,1);
    mainLayout->addWidget(new QLabel("Upust ceny C: "),5,2,1,1);
    mainLayout->addWidget(lineDiscountC = new QLineEdit(),5,3,1,1);
    mainLayout->addWidget(buttonSave= new Button(ButtonStruct("Zapisz","Zapisywanie dokonanych zmian", QSize(100,25))),3,4,1,1);
    mainLayout->addItem(new QSpacerItem(0,50,QSizePolicy::Maximum, QSizePolicy::Expanding),6,0,1,4);
}
void SettingsPricesView::setGraphicSettings()
{
    mainLayout->setColumnMinimumWidth(1,100);
    mainLayout->setColumnMinimumWidth(4,200);
    mainLayout->setRowMinimumHeight(2,20);
    mainLayout->setRowMinimumHeight(0,25);
    mainLayout->setRowMinimumHeight(4,40);
}
void SettingsPricesView::setInterfaceController()
{
    connect(buttonSave,SIGNAL(clicked()),controller,SLOT(saveSettings()));
}
QLineEdit* SettingsPricesView::getLineMarginaA(){return lineMarginA;}
QLineEdit* SettingsPricesView::getLineDiscountB(){return lineDiscountB;}
QLineEdit* SettingsPricesView::getLineDiscountC(){return lineDiscountC;}
