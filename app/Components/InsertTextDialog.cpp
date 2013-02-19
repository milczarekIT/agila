#include "InsertTextDialog.h"

InsertTextDialog::InsertTextDialog(QWidget *parent) :
    QDialog(parent)
{
    mainLayout = new QGridLayout();
    buttonBox = new ButtonBox(this);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    buttonBox->setMaximumHeight(40);
    mainLayout->addWidget(lineEdit = new  QLineEdit(),3,2,1,1);
    mainLayout->addWidget(buttonBox,4,0,1,0,Qt::AlignCenter);
    this->setLayout(mainLayout);
    this->setMinimumSize(300,100);
    this->setMaximumSize(300,100);
}

InsertTextDialog::~InsertTextDialog()
{
    delete mainLayout;
}


QLineEdit *InsertTextDialog::getLineEdit() {return lineEdit;}

void InsertTextDialog::signGenerating(QString value)
{
    if (value == "")this->lineEdit->setText("");
    else this->lineEdit->setText(value + "%");
}
