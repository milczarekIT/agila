#include "SettingsTaxesView.h"

SettingsTaxesView::SettingsTaxesView(SettingsTaxesController *controller,QWidget *parent) :
    SettingsAbstractItemView(parent)
{
    this->controller = controller;
    initGraphicElements();
    setGraphicSettings();
    setInterfaceController();
}

void SettingsTaxesView::initGraphicElements()
{
    mainLayout->addWidget(new QLabel("Definiowanie, Usuwanie oraz Edycja istniejących stawek VAT: "),1,1,1,4);
    //mainLayout->addWidget(pushRepaint = new Button(ButtonStruct("Odśwież","Odśwież tablicę stawek VAT", QSize(100,25))),1,4,1,1);
    mainLayout->addWidget(tableTaxes = new QTableWidget(),3,2,1,2);
    mainLayout->addWidget(pushNew = new Button(ButtonStruct("Nowy","Dodawanie nowej jednostki", QSize(100,25))),5,4,1,1);
    mainLayout->addWidget(pushEdit = new Button(ButtonStruct("Edytuj","Edycja wybranej jednostki", QSize(100,25))),6,4,1,1);
    mainLayout->addWidget(pushSave = new Button(ButtonStruct("Zapisz","Zapisywanie dokonanych zmian", QSize(100,25))),8,4,1,1);
    mainLayout->addWidget(pushDelete = new Button(ButtonStruct("Usun","Usuwanie wybranej jednostki", QSize(100,25))),7,4,1,1);
    mainLayout->addWidget(new QLabel("Typ: "),5,1,1,1);
    mainLayout->addWidget(new QLabel("Stawka Vat \nfaktury RR: "),4,1,1,1);
    mainLayout->addWidget(lineTaxForRR = new QLineEdit(),4,2,1,1);
    mainLayout->addWidget(boxName = new QComboBox(),5,2,1,1);
    mainLayout->addWidget(new QLabel("Wartość: "),7,1,1,1);
    mainLayout->addWidget(lineValue = new QLineEdit(),7,2,1,1);
    mainLayout->addWidget(new QLabel("Nazwa skrócona: "),8,1,1,1);
    mainLayout->addWidget(lineSign = new QLineEdit(),8,2,1,1);
    mainLayout->addItem(new QSpacerItem(0,50,QSizePolicy::Maximum, QSizePolicy::Expanding),9,0,1,5);
    lineTaxForRR->setToolTip("Kliknij dwukrotnie na tabelce powyżej aby wybrać");
    lineTaxForRR->setEnabled(false);
}

void SettingsTaxesView::setGraphicSettings()
{
     mainLayout->setColumnMinimumWidth(1,100);
     mainLayout->setRowMinimumHeight(0,25);
     mainLayout->setRowMinimumHeight(2,20);
     mainLayout->setRowMinimumHeight(4,40);
     mainLayout->setRowMinimumHeight(3,235);

     boxName->addItem("Stawka podstawowa");
     boxName->addItem("Stawka obniżona");
     boxName->addItem("Stawka zw.");
     boxName->setDisabled(true);

     lineValue->setValidator(new QRegExpValidator(QRegExp("[0-9]{1,2}[.]{1}[0-9]{0,2}"),lineValue));
     lineValue->setDisabled(true);
     lineSign->setDisabled(true);

     tableTaxes->setColumnCount(1);
     tableTaxes->setColumnWidth(0,591);
     tableTaxes->setHorizontalHeaderItem(0,new QTableWidgetItem("Nazwy"));
}

void SettingsTaxesView::setInterfaceController()
{
    connect(tableTaxes,SIGNAL(currentItemChanged(QTableWidgetItem*,QTableWidgetItem*)),controller,SLOT(setData()));
    connect(tableTaxes,SIGNAL(cellClicked(int,int)),controller,SLOT(setData()));
    connect(tableTaxes,SIGNAL(cellClicked(int,int)),controller,SLOT(changeActivate()));
    connect(pushEdit,SIGNAL(clicked()),controller,SLOT(editTax()));
    connect(pushNew,SIGNAL(clicked()),controller,SLOT(newTax()));
    connect(pushSave,SIGNAL(clicked()),controller,SLOT(saveTax()));
    //connect(pushRepaint,SIGNAL(clicked()),controller,SLOT(setModel()));
    connect(pushDelete,SIGNAL(clicked()),controller,SLOT(deleteTax()));
    connect(boxName,SIGNAL(activated(int)),controller,SLOT(enableRateNull()));
    connect(lineValue,SIGNAL(textChanged(QString)),controller,SLOT(signGenerating(QString)));
    connect(tableTaxes,SIGNAL(cellDoubleClicked(int,int)),controller,SLOT(setTaxIdData()));
}

SettingsTaxesView::~SettingsTaxesView()
{
}

void SettingsTaxesView::createItem(QTableWidgetItem *item, int i)
{
    item = new QTableWidgetItem();
    item->setText(taxes[i].getName());
    item->setData(Qt::UserRole, QVariant::fromValue(taxes[i].getId()));
    item->setToolTip("Zaznacz, by aktywować stawkę w programie.");

    if(taxes[i].isActiveInApp() == 1) item->setCheckState(Qt::Checked);
    else if(taxes[i].isActiveInApp() == 0) item->setCheckState(Qt::Unchecked);
    tableTaxes->setItem(i,0,item);
    if(i == 0) tableTaxes->setCurrentItem(item);
}

QLineEdit *SettingsTaxesView::getLineValue() {return lineValue;}
QLineEdit *SettingsTaxesView::getLineTaxId(){return lineTaxForRR;}
QLineEdit *SettingsTaxesView::getLineShortName(){return lineSign;}
QComboBox *SettingsTaxesView::getBoxName(){return boxName;}
Button *SettingsTaxesView::getPushNew(){return pushNew;}
Button *SettingsTaxesView::getPushEdit(){return pushEdit;}
Button *SettingsTaxesView::getPushSave(){return pushSave;}
Button *SettingsTaxesView::getPushDelete(){return pushDelete;}
QTableWidget *SettingsTaxesView::getTableTaxes(){return tableTaxes;}
QVector<Tax> SettingsTaxesView::getTaxes(){return taxes;}
void SettingsTaxesView::setTaxes(QVector<Tax> taxes){ this->taxes = taxes; }
