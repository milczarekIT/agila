#include "OfferView.h"

OfferView::OfferView(OfferController *controller, QWidget *parent) : PriceDocumentView(parent)
{
    this->controller = controller;
    setMainWidgets();
    initConnections();
    setGUISettings();
}

void OfferView::setMainWidgets() {
    PriceDocumentView::setMainWidgets();
    layout->addWidget(selectContractor, 1, 2);
}

QGroupBox *OfferView::setMainInfoWidgets() {

    QGroupBox *mainInfos = new QGroupBox("Informacje o ofercie");
    QGridLayout *mainInfoLayout = new QGridLayout(mainInfos);
    int row = 1, col = 0;

    mainInfoLayout->addWidget(new QLabel("<b>Symbol: </b>"), row++, col);
    mainInfoLayout->addWidget(new QLabel("Data utworzenia: "), row++, col);
    mainInfoLayout->addWidget(new QLabel("Poziom cen: "), row++, col);
    mainInfoLayout->addWidget(new QLabel("Obowiązuje od: "), row++, col);
    mainInfoLayout->addWidget(new QLabel("Obowiązuje do:"), row++, col);

    row = 1, col = 1;

    mainInfoLayout->addWidget(sign, row++, col);
    mainInfoLayout->addWidget(createDate, row++, col);
    mainInfoLayout->addWidget(priceLevel, row++, col);
    mainInfoLayout->addWidget(dateFrom, row++, col);
    mainInfoLayout->addWidget(dateTo, row++, col);
    mainInfoLayout->addWidget(notConcerns, row++, col++, 1, 1, Qt::AlignLeft);

    row = 1;
    mainInfoLayout->addWidget(contractorData, row, ++col, 5, 3, Qt::AlignRight);

    mainInfoLayout->setColumnMinimumWidth(2, 30);
    mainInfoLayout->setColumnMinimumWidth(1, 300);
    return mainInfos;
}

void OfferView::initWidgets() {
    PriceDocumentView::initWidgets();

    selectContractor = new Button(ButtonStruct("Wybierz","Wybierz","chooseContractor",QSize(100,28)),QSize(25,25));
    contractorData = new QTextEdit();
    mainInfos = setMainInfoWidgets();
}

void OfferView::setGUISettings() {
    PriceDocumentView::setGUISettings();

    this->setWindowTitle("Oferty");
    contractorData->setDisabled(true);
}

void OfferView::initConnections() {

    connect(notConcerns,SIGNAL(toggled(bool)),controller,SLOT(setDateLikeNotConcerns(bool)));
    connect(chooseGood,SIGNAL(clicked()),controller,SLOT(selectGoods()));
    connect(buttonBox, SIGNAL(accepted()), controller,SLOT(checkRequiredFields()));
    connect(buttonBox, SIGNAL(rejected()), controller, SLOT(checkChanges()));
    connect(deleteGood, SIGNAL(clicked()), controller, SLOT(removeGoodsFromPositions()));
    connect(selectContractor, SIGNAL(clicked()), controller, SLOT(selectContractor()));
    connect(priceLevel, SIGNAL(activated(int)), controller, SLOT(initTableModel()));
}

QTextEdit *OfferView::getContractorData() {
    return contractorData;
}

QLineEdit *OfferView::getName() {
}

QTextEdit *OfferView::getDescribe() {
}

QString OfferView::getSymbol() {
    return "OF";
}
