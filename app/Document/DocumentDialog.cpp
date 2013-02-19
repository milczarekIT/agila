#include "DocumentDialog.h"

DocumentDialog::DocumentDialog(QWidget *parent) : QDialog(parent){

    this->mainLayout = new QGridLayout;
    initGoodsTable();
    initLabels();
    initLineEdits();
    initButtons();
}

void DocumentDialog::initLineEdits()   {
    lineDocumentSymbol = new QLineEdit();
    lineDocumentPlace = new QLineEdit();

    lineName = new QLineEdit();
    linePostCode = new QLineEdit();
    lineCity = new QLineEdit();
    lineAddress = new QLineEdit();
    lineTIN = new QLineEdit();
    lineRegon = new QLineEdit();

    lineGoodsValue = new QLineEdit();
    lineGoodsValue->setModified(false); //cos nie trybi...

}

void DocumentDialog::initLabels()  {
    labelDocumentSymbol = new QLabel(trUtf8("Symbol dokumentu:"));
    labelDocumentPlace = new QLabel(trUtf8("Miejsce wystawienia:"));
    labelIssueDate = new QLabel(trUtf8("Data wystawienia:"));


    labelName = new QLabel(trUtf8("Nazwa:"));
    labelPostCode = new QLabel(trUtf8("Kod pocztowy:"));
    labelCity = new QLabel(trUtf8("Miasto:"));
    labelAddress = new QLabel(trUtf8("Adres:"));
    labelTIN = new QLabel(trUtf8("NIP:"));
    labelRegon = new QLabel(trUtf8("Regon:"));

    labelGoodsValue = new QLabel(trUtf8("Wartość towarów:"));

}

void DocumentDialog::initGoodsTable()    {
    goodsTable = new TableView();
    goodsTVModel = new GoodsTVModel();
    goodsTVModel->getGoods();
    goodsTable->setGoodsModel(goodsTVModel);
}

void DocumentDialog::initButtons()  {
    buttonBox = new QDialogButtonBox(Qt::Horizontal, this);
    buttonBox->addButton("Anuluj", QDialogButtonBox::RejectRole);
    buttonBox->addButton("Zapisz", QDialogButtonBox::AcceptRole);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    buttonChangeContractor = new QPushButton(trUtf8("Zmień"));
    buttonGoodAdd = new QPushButton(trUtf8("Dodaj"));
    buttonGoodEdit = new QPushButton(trUtf8("Edytuj"));
    buttonGoodDel = new QPushButton(trUtf8("Usuń"));

}

