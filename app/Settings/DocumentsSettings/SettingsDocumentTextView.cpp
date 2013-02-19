#include "SettingsDocumentTextView.h"

SettingsDocumentTextView::SettingsDocumentTextView(SettingsDocumentTextController *controller,QWidget *parent) :
        SettingsAbstractItemView(parent)
{
    this->controller = controller;
    initGraphicElements();
    setGraphicSettings();
    setInterfaceController();
}

SettingsDocumentTextView::~SettingsDocumentTextView()
{
}

void SettingsDocumentTextView::initGraphicElements()
{
    mainLayout->addWidget(new QLabel("Edycja tekstu znajdującego się pod wybranym dokumentem: "),1,0,1,4);
    mainLayout->addWidget(tableDTextes = new QTableWidget(),3,1,1,2);
    mainLayout->addItem(new QSpacerItem(0,50,QSizePolicy::Maximum, QSizePolicy::Expanding),4,0,1,4);
}

void SettingsDocumentTextView::setGraphicSettings()
{
    mainLayout->setRowMinimumHeight(0,27);
    mainLayout->setRowMinimumHeight(2,27);
    mainLayout->setRowMinimumHeight(3,295);
    mainLayout->setColumnMinimumWidth(1,300);
    mainLayout->setColumnMinimumWidth(2,300);
}

void SettingsDocumentTextView::setTableSettings()
{
    tableDTextes->setColumnWidth(0,150);
    tableDTextes->setColumnWidth(1,417);
    tableDTextes->setHorizontalHeaderItem(0,new QTableWidgetItem("Typ dokumentu"));
    tableDTextes->setHorizontalHeaderItem(1,new QTableWidgetItem("Tekst"));
}

void SettingsDocumentTextView::setInterfaceController()
{
    connect(tableDTextes,SIGNAL(cellChanged(int,int)),controller,SLOT(acceptAction()));
}

void SettingsDocumentTextView::createItem(int i)
{
    QTableWidgetItem *item = new QTableWidgetItem();
    QTableWidgetItem *item2 = new QTableWidgetItem();
    isEdited = false;
    item->setText(documentsInfo[i].getName());
    item->setFlags(Qt::ItemIsEnabled);
    tableDTextes->setItem(i,0,item);
    isEdited = false;
    item2->setText(documentsInfo[i].getAfterText());
    item2->setToolTip("Kliknij dwukrotnie, aby edytować");
    tableDTextes->setItem(i,1,item2);
}

QTableWidget *SettingsDocumentTextView::getTableDTextes() {return tableDTextes;}
QVector<DocumentInfo> SettingsDocumentTextView::getDocumentsInfo() {return documentsInfo;}
void SettingsDocumentTextView::setDocumentsInfo(QVector<DocumentInfo> documentsInfo) { this->documentsInfo = documentsInfo; }
void SettingsDocumentTextView::setIsEdited(bool isEdited) {this->isEdited = isEdited;}
bool SettingsDocumentTextView::getIsEdited() {return isEdited;}
