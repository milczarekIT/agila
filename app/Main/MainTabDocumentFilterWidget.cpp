#include "MainTabDocumentFilterWidget.h"

MainTabDocumentFilterWidget::MainTabDocumentFilterWidget(QString documentFamily, QWidget *parent) :
    QWidget(parent)
{
    this->layout = new QGridLayout();
    this->setLayout(layout);
    this->documentFamily = documentFamily;

    this->addAllComponents();
    this->initData();
}

void MainTabDocumentFilterWidget::addAllComponents()
{
    this->layout->addWidget(new QLabel("Typ dokumentów:   "),0,0); // +12
    this->layout->addWidget(new QLabel("Od"),0,3,Qt::AlignRight);
    this->layout->addWidget(new QLabel("Do"),0,6,Qt::AlignRight);
    this->layout->addWidget(comboboxDocumentsTypes = new QComboBox(),0,1);
    this->layout->addWidget(fromDateEdit = new DateEdit(),0,4);
    this->layout->addWidget(toDateEdit = new DateEdit(),0,7);
    this->layout->setColumnMinimumWidth(2,30);
    this->layout->setColumnMinimumWidth(5,30);
    this->layout->addItem(new QSpacerItem(20,0, QSizePolicy::Expanding, QSizePolicy::Minimum),0,8,1,1);
    this->comboboxDocumentsTypes->setMinimumWidth(260);
}

void MainTabDocumentFilterWidget::initData()
{
    fromDateEdit->setDate(QDate(QDate::currentDate().year(), 1, 1));
    toDateEdit->setDate(QDate(QDate::currentDate().year(), 12, 31));

    DocumentInfoModel *docInfoModel = new DocumentInfoModel();
    comboboxDocumentsTypes->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    comboboxDocumentsTypes->setStatusTip("Wybierz typ dokumentów");
    comboboxDocumentsTypes->addItem("Wszystkie", QVariant(""));
    fillComboBox(comboboxDocumentsTypes, docInfoModel->getDocumentsInfo(documentFamily));

    connect(comboboxDocumentsTypes, SIGNAL(currentIndexChanged(int)), this, SLOT(documentTypeChanged(int)));
    connect(fromDateEdit, SIGNAL(dateChanged(QDate)), this, SIGNAL(fromDateChanged(QDate)));
    connect(toDateEdit, SIGNAL(dateChanged(QDate)), this, SIGNAL(toDateChanged(QDate)));
}

void MainTabDocumentFilterWidget::fillComboBox(QComboBox *box,QVector<DocumentInfo> values)
{
    for(int i = 0; i < values.size(); i++)
        box->addItem(values[i].getName() + " (" + values[i].getType() + ")", QVariant::fromValue(values[i].getType()));
}

void MainTabDocumentFilterWidget::documentTypeChanged(int index) // slot
{
    QString documentType = comboboxDocumentsTypes->itemData(index).toString();
    emit documentTypeChanged(documentType); // sygnał
}

QString MainTabDocumentFilterWidget::getDocumentType()
{
    int currentIndex = comboboxDocumentsTypes->currentIndex();

    return comboboxDocumentsTypes->itemData(currentIndex).toString();
}

QDate MainTabDocumentFilterWidget::getFromDate()
{
    return fromDateEdit->date();
}

QDate MainTabDocumentFilterWidget::getToDate()
{
    return toDateEdit->date();
}
