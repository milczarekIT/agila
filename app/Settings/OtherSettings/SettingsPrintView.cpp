#include "SettingsPrintView.h"

SettingsPrintView::SettingsPrintView(SettingsPrintController *controller, QWidget *parent) :
        SettingsAbstractItemView(parent)
{
    this->controller = controller;
    initGraphicElements();
    setGraphicSettings();
    setInterfaceController();
}

void SettingsPrintView::initGraphicElements()
{
    mainLayout->addWidget(new QLabel("Ustawienia parametrów drukowania: "),1,1,1,5);
    mainLayout->addItem(new QSpacerItem(0,50,QSizePolicy::Maximum, QSizePolicy::Expanding),2,0,1,5);
}

void SettingsPrintView::setGraphicSettings()
{
    mainLayout->setRowMinimumHeight(0,25);
    mainLayout->setRowMinimumHeight(2,20);
}

void SettingsPrintView::setInterfaceController()
{
}
