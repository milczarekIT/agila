#include "AddGroup.h"

AddGroup::AddGroup(QWidget *parent) : InsertTextDialog()
{

    mainLayout->addWidget(new QLabel("Typ: "),1,1,1,1);
    mainLayout->addWidget(boxName = new QComboBox(),1,2,1,1);
    mainLayout->addWidget(new QLabel("Wartość: "),2,1,1,1);
    mainLayout->addWidget(lineSign = new QLineEdit(),2,2,1,1);
    mainLayout->addWidget(new QLabel("Nazwa skrócona: "),3,1,1,1);
    lineSign->setFocus();
    lineSign->setValidator(new QRegExpValidator(QRegExp("[0-9]{1,2}[.]{1}[0-9]{0,2}"),lineSign));
    boxName->addItem("Stawka podstawowa");
    boxName->addItem("Stawka obniżona");
    connect(lineSign,SIGNAL(textChanged(QString)),this,SLOT(signGenerating(QString)));
    this->setMinimumSize(370,150);
    this->setMaximumSize(370,150);
}

AddGroup::~AddGroup()
{
}

QComboBox*AddGroup::getBoxName()
{
    return this->boxName;
}
QLineEdit*AddGroup::getLineValue()
{
    return this->lineSign;
}


