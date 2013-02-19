#include "SettingsMagazineItemView.h"

SettingsMagazineItemView::SettingsMagazineItemView(WarehouseService *service,Warehouse warehouse,SettingsMagazineItemController *controller,QWidget *parent) :
    QFrame(parent)
{
    this->controller = controller;
    this->warehouse = warehouse;
    this->service = service;
    initGraph();
    setGraphSettings();
    setInterfaceController();
}

void SettingsMagazineItemView::initGraph()
{
    this->setLayout(mainLayout = new QGridLayout);
    mainLayout->addWidget(widgetValue = new QLabel("<b>"+ warehouse.getName() +"</b>"),1,1,1,3);
    mainLayout->addWidget(new QLabel("Krótka nazwa:"),3,2,1,1);
    mainLayout->addWidget(new QLabel("Nazwa magazynu:"),5,2,1,1);
    mainLayout->addWidget(warehouseShortName = new QLineEdit(warehouse.getShortName()),3,3,1,3);
    warehouseShortName->setMaxLength(4);
    mainLayout->addWidget(warehouseName = new QLineEdit(warehouse.getName()),5,3,1,3);
    mainLayout->addWidget(editWarehouse = new QPushButton("Edutuj"),1,4,1,1);
    mainLayout->addWidget(deleteStore = new QPushButton("Usuń"),1,5,1,1);
    mainLayout->addWidget(labelDefautWarehouse = new QLabel("<font color=\"green\">Domyślny</font>"),1,3,1,1);
}

void SettingsMagazineItemView::setGraphSettings()
{
    this->setFrameShape(QFrame::Box);
    this->setFrameShadow(QFrame::Raised);
    this->setMaximumHeight(120);
    this->setMinimumHeight(120);
    this->setMinimumWidth(650);
    this->setProperty("storeItem",true);
    mainLayout->setColumnMinimumWidth(1,50);
    warehouseShortName->setDisabled(true);
    warehouseName->setDisabled(true);
}

void SettingsMagazineItemView::setInterfaceController()
{
    connect(editWarehouse,SIGNAL(clicked()),controller,SLOT(emitEditSignal()));
    connect(deleteStore,SIGNAL(clicked()),controller,SLOT(emitDeleteSignal()));
}

QLabel *SettingsMagazineItemView::getLabelDefaultWarehouse() { return labelDefautWarehouse; }
QLineEdit *SettingsMagazineItemView::getWarehouseName() { return this->warehouseName; }
QLineEdit *SettingsMagazineItemView::getWarehouseShortName() { return this->warehouseShortName; }
QLabel *SettingsMagazineItemView::getWidgetValue() { return widgetValue; }
Warehouse SettingsMagazineItemView::getWarehouse() { return warehouse;}
void SettingsMagazineItemView::setWarehouse(Warehouse warehouse) { this->warehouse = warehouse;}
