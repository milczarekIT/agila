#include "StoreDocumentView.h"

StoreDocumentView::StoreDocumentView(QWidget *parent) : DocumentView(parent)
{
}

StoreDocumentView::~StoreDocumentView(){}


void StoreDocumentView::addOptionalComponents() {

    QRegExpValidator *validator = new QRegExpValidator(QRegExp("[0-9]+([.]|,)[0-9]{2}"),this);
    checkStoreUpdating->setChecked(true);
    mainLayout->addWidget(new QLabel("Skutek magazynowy:"),1,4);
    mainLayout->addWidget(checkStoreUpdating,1,5);
    mainLayout->addWidget( new QLabel("Razem netto:"), 8, 0);
    mainLayout->addWidget(lineGoodsValueNet, 8, 1);
    lineGoodsValueNet->setValidator(validator);
    lineGoodsValueNet->setReadOnly(true);
    lineGoodsValue->setVisible(false);
    labelGoodsValue->setVisible(false);

}

void StoreDocumentView::initOptionalLineEdits() {

    lineGoodsValueNet= new QLineEdit();
    lineReceiveName = new QLineEdit();
    checkStoreUpdating = new QCheckBox();
}

void StoreDocumentView::initGoodsTable()  {

  goodsTable = new QTableWidget();
  goodsTable->setColumnCount(6);
  goodsTable->setColumnWidth(0,300);
  goodsTable->setColumnWidth(1,230);
  goodsTable->setColumnWidth(2,120);
  goodsTable->setColumnWidth(3,120);
  goodsTable->setColumnWidth(4,110);
  goodsTable->setColumnWidth(5,110);
  goodsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
  setHeaders(0,new QTableWidgetItem("Nazwa"));
  setHeaders(1,new QTableWidgetItem("Symbol"));
  setHeaders(2,new QTableWidgetItem("Cena Netto"));
  setHeaders(3,new QTableWidgetItem("Cena Brutto"));
  setHeaders(4,new QTableWidgetItem("Ilość"));
  setHeaders(5,new QTableWidgetItem("Wartość brutto"));
}

double StoreDocumentView::getLineGoodsValueNet(){return this->lineGoodsValueNet->text().toDouble();}

bool StoreDocumentView::isStoreUpdating()
{
    return this->checkStoreUpdating->isChecked();
}

void StoreDocumentView::setLineGoodsValueNet(double valueNet)
{
      QString str = QVariant(valueNet).toString();
    this->lineGoodsValueNet->setText(str.setNum(valueNet,',',2).replace(QRegExp("[.]"),","));
}
void StoreDocumentView::setCheckStoreUpdate(bool update){this->checkStoreUpdating->setChecked(update);}
void StoreDocumentView::initOptionalButtons(){};
void StoreDocumentView::initOptionalConnections(){};
