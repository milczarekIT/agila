#include "SettingsOwnerView.h"

SettingsOwnerView::SettingsOwnerView(SettingsOwnerController *controller, QWidget *parent):
        SettingsAbstractItemView(parent)
{
    this->controller = controller;
    initGraphicElements();
    setGraphicSettings();
    setInterfaceController();
}

void SettingsOwnerView::initGraphicElements()
{
    mainLayout->addWidget(new QLabel("Edycja danych podmiotu: "),1,1,1,12);
    mainLayout->addWidget(new QLabel("Nazwa firmy: "),3,1,1,3);
    mainLayout->addWidget(new QLabel("Adres: "),4,1,1,3);

    mainLayout->addWidget(new QLabel("Kod pocztowy: "),5,1,1,3);
    mainLayout->addWidget(new QLabel("Miasto: "),5,7,1,3);
    mainLayout->addWidget(new QLabel("NIP: "),6,1,1,3);
    mainLayout->addWidget(new QLabel("Nazwa banku: "),7,1,1,3);
    mainLayout->addWidget(new QLabel("Numer konta bankowego: "),8,1,1,3);
    mainLayout->addWidget(new QLabel("Adres eMail: "),10,1,1,3);
    mainLayout->addWidget(new QLabel("Strona internetowa: "),11,1,1,3);
    mainLayout->addWidget(new QLabel("Dodatkowe: "),12,1,1,3);
    mainLayout->addWidget(new QLabel("Telefony: "),10,10,1,3);
    mainLayout->addWidget(lineName = new QLineEdit(),3,4,1,9);
    mainLayout->addWidget(lineAdress = new QLineEdit(),4,4,1,9);
    mainLayout->addWidget(linePostCode = new QLineEdit(),5,4,1,3);
    mainLayout->addWidget(lineCity = new QLineEdit(),5,10,1,3);
    mainLayout->addWidget(pushSetLogo = new Button(ButtonStruct("Ustaw logo","Wybierz zdjęcie z dysku, które ma być twoim logiem", QSize(100,25))),6,7,1,3, Qt::AlignRight);
    mainLayout->addWidget(lineNIP = new QLineEdit(),6,4,1,3);
    mainLayout->addWidget(pushRemoveLogo = new Button(ButtonStruct("Usuń logo","Usuń aktualne logo", QSize(100,25))),7,7,1,3, Qt::AlignRight);
    mainLayout->addWidget(lineBankName = new QLineEdit(),7,4,1,3);
    mainLayout->addWidget(lineBankAccount = new QLineEdit(),8,4,1,6);
    mainLayout->addWidget(lineEMail = new QLineEdit(),10,4,1,6);
    mainLayout->addWidget(lineWebsite = new QLineEdit(),11,4,1,6);
    mainLayout->addWidget(linePhone1 = new QLineEdit(),11,10,1,3);
    mainLayout->addWidget(linePhone2 = new QLineEdit(),12,10,1,3);
    mainLayout->addWidget(linePhone3 = new QLineEdit(),13,10,1,3);
    mainLayout->addWidget(textAdditional = new QTextEdit(),12,4,3,6);
    mainLayout->addWidget(logo = new QLabel("  Brak zdefiniowanego\n        logo"),6,10,4,3);
    mainLayout->addWidget(pushSave = new Button(ButtonStruct("Zapisz zmiany","Zapisz zmiany dokonane w danych podmiotu", QSize(500,25))),18,1,1,15,Qt::AlignCenter);
}

void SettingsOwnerView::setGraphicSettings()
{
    mainLayout->setRowMinimumHeight(0,25);
    mainLayout->setRowMinimumHeight(2,20);
    mainLayout->setRowMinimumHeight(11,20);
    mainLayout->setRowMinimumHeight(17,20);
    mainLayout->setRowMinimumHeight(19,25);

    lineName->setMaxLength(70);
    lineAdress->setMaxLength(60);
    linePostCode->setValidator(new QRegExpValidator(QRegExp("[0-9]{2}[-]{1}[0-9]{3}"),linePostCode));
    lineCity->setMaxLength(40);
    lineNIP->setValidator(new QRegExpValidator(QRegExp("[0-9]{3}[-]{1}[0-9]{3}[-]{1}[0-9]{2}[-]{1}[0-9]{2}"),lineNIP));
    lineBankName->setMaxLength(25);
    lineBankAccount->setValidator(new QRegExpValidator(QRegExp("[0-9]{2}( [0-9]{4}){6}"),lineBankAccount));
    lineEMail->setMaxLength(60);
    lineWebsite->setMaxLength(60);
    linePhone1->setMaxLength(20);
    linePhone2->setMaxLength(20);
    linePhone3->setMaxLength(20);
    logo->setFrameShape(QFrame::Box);
    logo->setMaximumHeight(115);
    logo->setMinimumHeight(115);
    logo->setMinimumWidth(175);
    logo->setMaximumWidth(175);
}

void SettingsOwnerView::setInterfaceController()
{
    connect(linePostCode, SIGNAL(editingFinished()), controller, SLOT(autoPostalCode()));
    connect(pushSetLogo,SIGNAL(clicked()),controller,SLOT(setLogo()));
    connect(pushRemoveLogo,SIGNAL(clicked()),controller,SLOT(removeLogo()));
    connect(pushSave,SIGNAL(clicked()),controller,SLOT(saveData()));
}

QLineEdit *SettingsOwnerView::getLineName() {return lineName;}
QLineEdit *SettingsOwnerView::getLineAdress() {return lineAdress;}
QLineEdit *SettingsOwnerView::getLinePostCode() {return linePostCode;}
QLineEdit *SettingsOwnerView::getLineCity() {return lineCity;}
QLineEdit *SettingsOwnerView::getLineNIP() {return lineNIP;}
QLineEdit *SettingsOwnerView::getLineBankName() {return lineBankName;}
QLineEdit *SettingsOwnerView::getLineBankAccount() {return lineBankAccount;}
QLineEdit *SettingsOwnerView::getLineEMail() {return lineEMail;}
QLineEdit *SettingsOwnerView::getLineWebsite() {return lineWebsite;}
QLineEdit *SettingsOwnerView::getLinePhone1() {return linePhone1;}
QLineEdit *SettingsOwnerView::getLinePhone2() {return linePhone2;}
QLineEdit *SettingsOwnerView::getLinePhone3() {return linePhone3;}
QTextEdit *SettingsOwnerView::getTextAdditional() {return textAdditional;}
Button *SettingsOwnerView::getPushSave() {return pushSave;}
Button *SettingsOwnerView::getPushRemoveLogo() { return pushRemoveLogo; }
Button *SettingsOwnerView::getPushSetLogo() { return pushSetLogo; }
QLabel *SettingsOwnerView::getLogo() {return logo;}
