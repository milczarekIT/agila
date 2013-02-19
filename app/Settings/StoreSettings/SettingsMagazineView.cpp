#include "SettingsMagazineView.h"

SettingsMagazineView::SettingsMagazineView(SettingsMagazineController *controller,QWidget *parent) :
    QWidget(parent)
{
    this->controller = controller;
    warehouseService = new WarehouseService();
    initGraph();
}

SettingsMagazineView::~SettingsMagazineView() {
    delete warehouseService;
}

void SettingsMagazineView::initGraph()
{
    this->setLayout(mainLayout = new QGridLayout);
    mainLayout->addWidget(addNewStore = new QPushButton("Dodaj nowy magazyn"),2,1,1,2);
    setItems();

    connect(addNewStore,SIGNAL(clicked()),controller,SLOT(addWarehouse()));
}

void SettingsMagazineView::setItems()
{
    warehousesList = new QWidget;
    scrollArea = new QScrollArea;
    warehousesList->setLayout(warehousesLayout = new QGridLayout);
    mainLayout->addWidget(scrollArea,0,1,1,2);

    warehouses = warehouseService->getWarehouses();

    itr = warehouses.count();
    items = new SettingsMagazineItemController*[itr]();

    for (int i=0;i<itr;i++)
    {
        items[i] = new SettingsMagazineItemController(warehouseService,warehouses[i]);
        warehousesLayout->addWidget(items[i]->getView(),i,1,1,2);

        connect(items[i],SIGNAL(editButtonClicked(int)),controller,SLOT(editWarehouse(int)));
        connect(items[i],SIGNAL(removeButtonClicked(int)),controller,SLOT(removeWarehouse(int)));
        connect(items[i],SIGNAL(checkWarehouse(int)),controller,SLOT(emitMagazineChanged()));

        if(warehouses[i].isDefaultWarehouse())
            items[i]->getView()->getLabelDefaultWarehouse()->setVisible(true);
        else
            items[i]->getView()->getLabelDefaultWarehouse()->setVisible(false);
    }
    scrollArea->setWidget(warehousesList);
    scrollArea->setProperty("raportsWidget",true);
    warehousesList->setProperty("raportsWidget",true);

    emit numberOfMagazinesChanged();
}

void SettingsMagazineView::deleteWidgets()
{
    delete warehousesLayout;
    delete warehousesList;
    delete scrollArea;
    setItems();
}

void SettingsMagazineView::setWarehouses(QVector<Warehouse>  warehouses)
{
    this->warehouses = warehouses;
}

QVector<Warehouse> SettingsMagazineView::getWarehouses() {return warehouses;}
int SettingsMagazineView::getIterator() { return itr;}
SettingsMagazineItemController **SettingsMagazineView::getItems() { return items;}
