#include "PriceDocumentView.h"

PriceDocumentView::PriceDocumentView(QWidget *parent) :
    QDialog(parent)
{
}

void PriceDocumentView::initConnections() {
}

QGroupBox *PriceDocumentView::setMainInfoWidgets() {
}

void PriceDocumentView::setGUISettings() {
    this->setMinimumSize(880,600);
    this->mainInfos->setMaximumSize(750,230);
    this->layout->setRowMinimumHeight(2,20);
    this->setDateLastDayOfMonth(dateTo);
    this->sign->setEnabled(false);
    getPositions()->setSelectionMode(QAbstractItemView::SingleSelection);
    getPositions()->setSelectionBehavior(QAbstractItemView::SelectRows);
    initTableHeaders();
}

void PriceDocumentView::setMainWidgets() {

    initWidgets();
    this->setLayout(layout);
    int row = 1, col = 1;

    layout->addWidget(mainInfos, row++, col, Qt::AlignRight);
    layout->addWidget(positions, ++row, col++, 15, 1);
    layout->addWidget(chooseGood, row++, col,Qt::AlignTop);
    layout->addWidget(deleteGood, row++, col--,Qt::AlignTop);

    row = 19;
    layout->addWidget(buttonBox, row, col, 1, 2, Qt::AlignRight);
}

void PriceDocumentView::initWidgets() {

    layout = new QGridLayout;
    positions = new QTableWidget;
    sign = new QLineEdit;
    createDate = new DateEdit;
    dateFrom = new DateEdit;
    dateTo = new DateEdit;
    notConcerns = new QRadioButton("nie dotyczy");
    priceLevel = new QComboBox;

    buttonBox = createButtonBox();
    chooseGood = new Button(ButtonStruct("Wybierz","Wybierz","chooseGood",QSize(100,28)),QSize(25,25));
    deleteGood = new Button(ButtonStruct("   Usuń","   Usuń","del",QSize(100,28)),QSize(20,20));
}

QDialogButtonBox *PriceDocumentView::createButtonBox() {

    QDialogButtonBox *buttonBox = new QDialogButtonBox(Qt::Horizontal, this);
    buttonBox->addButton("Anuluj", QDialogButtonBox::RejectRole);
    buttonBox->addButton("Zapisz", QDialogButtonBox::AcceptRole);
    return buttonBox;
}

void PriceDocumentView::setDateLastDayOfMonth(DateEdit *dateEdit) {

    QDate date = QDate::currentDate();
    int day = date.daysInMonth();
    date.setDate(date.year(), date.month(), day);
    dateEdit->setDate(date);
    initTableHeadersSize();
    initTableHeaders();
}

void PriceDocumentView::initTableHeaders() {

    int col = 0;
    this->getPositions()->setHorizontalHeaderItem(col++, new QTableWidgetItem("Id"));
    this->getPositions()->setHorizontalHeaderItem(col++, new QTableWidgetItem("Nazwa"));
    this->getPositions()->setHorizontalHeaderItem(col++, new QTableWidgetItem("Symbol"));
    this->getPositions()->setHorizontalHeaderItem(col++, new QTableWidgetItem("j.m."));
    this->getPositions()->setHorizontalHeaderItem(col++, new QTableWidgetItem("Cena netto"));
    this->getPositions()->setHorizontalHeaderItem(col++, new QTableWidgetItem("Cena brutto"));
}

void PriceDocumentView::initTableHeadersSize() {

    int col = 0;
    this->getPositions()->setColumnCount(6);
    this->getPositions()->setColumnWidth(col++,10);
    this->getPositions()->setColumnWidth(col++,235);
    this->getPositions()->setColumnWidth(col++,235);
    this->getPositions()->setColumnWidth(col++,50);
    this->getPositions()->setColumnWidth(col++,100);
    this->getPositions()->setColumnWidth(col++,100);
    this->getPositions()->setColumnHidden(0,true);
}

QGroupBox *PriceDocumentView::getMainInfos() {
    return mainInfos;
}

QLineEdit *PriceDocumentView::getSign() {
    return sign;
}

DateEdit *PriceDocumentView::getCreateDate() {
    return createDate;
}

DateEdit *PriceDocumentView::getDateFrom() {
    return dateFrom;
}

DateEdit *PriceDocumentView::getDateTo() {
    return dateTo;
}

QRadioButton *PriceDocumentView::getNotConcerns() {
    return notConcerns;
}

QTableWidget *PriceDocumentView::getPositions() {
    return positions;
}

Button *PriceDocumentView::getChooseGood() {
    return chooseGood;
}

QDialogButtonBox *PriceDocumentView::getButtonBox() {
    return buttonBox;
}

Button *PriceDocumentView::getDeleteGood() {
    return deleteGood;
}

QComboBox *PriceDocumentView::getPriceLevel() {
    return priceLevel;
}

QString PriceDocumentView::getSymbol() {
    return "price_lists";
}
