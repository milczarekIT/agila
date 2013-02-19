#include "SettingsPriceSelectionView.h"

SettingsPriceSelectionView::SettingsPriceSelectionView(SettingsPriceSelectionController *controller, QWidget *parent) :
        SettingsAbstractItemView(parent)
{
    this->controller = controller;
    initGraphicElements();
    setGraphicSettings();
    setInterfaceController();
}

void SettingsPriceSelectionView::initGraphicElements()
{
    mainLayout->addWidget(new QLabel("Wystaw fakturę przeliczoną według ceny: "),1,0,1,6);
    mainLayout->addWidget(net = new QLabel(),4,1);
    mainLayout->addWidget(gross = new QLabel(),4,3);
    mainLayout->addWidget(radioNet = new QRadioButton("Netto"),5,1);
    mainLayout->addWidget(radioGross = new QRadioButton("Brutto"),5,3);
    mainLayout->addItem(new QSpacerItem(0,50,QSizePolicy::Maximum, QSizePolicy::Expanding),6,0,1,5);
}

void SettingsPriceSelectionView::setGraphicSettings()
{

    mainLayout->setColumnMinimumWidth(1,100);
    mainLayout->setColumnMinimumWidth(2,110);
    mainLayout->setRowMinimumHeight(0,25);
    mainLayout->setRowMinimumHeight(2,20);
}

void SettingsPriceSelectionView::setInterfaceController()
{
    connect(radioGross,SIGNAL(clicked()),controller,SLOT(changeDefault()));
    connect(radioNet,SIGNAL(clicked()),controller,SLOT(changeDefault()));
}

QRadioButton *SettingsPriceSelectionView::getRadioGross() { return radioGross;}
QRadioButton *SettingsPriceSelectionView::getRadioNet() { return radioNet;}
