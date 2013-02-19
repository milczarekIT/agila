#include "PriceListView.h"

PriceListView::PriceListView(PriceListController *controller, QWidget *parent) : PriceDocumentView(parent)
{
    this->controller = controller;
    setMainWidgets();
    initConnections();
    setGUISettings();
}

QGroupBox *PriceListView::setMainInfoWidgets() {

    QGroupBox *mainInfos = new QGroupBox("Informacje o cenniku");
    QGridLayout *mainInfoLayout = new QGridLayout(mainInfos);
    int row = 1, col = 0;

    mainInfoLayout->addWidget(new QLabel("<b>Symbol: </b>"), row++, col);
    mainInfoLayout->addWidget(new QLabel("<b>Nazwa: </b>"), row++, col);
    mainInfoLayout->addWidget(new QLabel("Data utworzenia: "), row++, col);
    mainInfoLayout->addWidget(new QLabel("Poziom cen: "), row++, col);
    mainInfoLayout->addWidget(new QLabel("Opis: "), row++, col);

    row = 1, col = 3;

    mainInfoLayout->addWidget(new QLabel("Obowiązuje od: "), row++, col);
    mainInfoLayout->addWidget(new QLabel("Obowiązuje do:"), row++, col);

    row = 1, col = 1;

    mainInfoLayout->addWidget(sign, row++, col);
    mainInfoLayout->addWidget(name, row++, col);
    mainInfoLayout->addWidget(createDate, row++, col);
    mainInfoLayout->addWidget(priceLevel, row++, col);
    mainInfoLayout->addWidget(describe, row++, col, 1, 4);

    row = 1, col = 4;

    mainInfoLayout->addWidget(dateFrom, row++, col);
    mainInfoLayout->addWidget(dateTo, row++, col--);
    mainInfoLayout->addWidget(notConcerns, row++, col, 1, 2, Qt::AlignRight);

    mainInfoLayout->setColumnMinimumWidth(1,300);
    mainInfoLayout->setColumnMinimumWidth(4,200);
    mainInfoLayout->setColumnMinimumWidth(2,10);
    return mainInfos;
}

void PriceListView::initWidgets() {
    PriceDocumentView::initWidgets();

    name = new QLineEdit;
    describe = new QTextEdit;
    mainInfos = setMainInfoWidgets();
}

void PriceListView::setGUISettings() {
    PriceDocumentView::setGUISettings();
    this->setWindowTitle("Cennik");
}

void PriceListView::initConnections() {

    connect(notConcerns,SIGNAL(toggled(bool)),controller,SLOT(setDateLikeNotConcerns(bool)));
    connect(chooseGood,SIGNAL(clicked()),controller,SLOT(selectGoods()));
    connect(buttonBox, SIGNAL(accepted()), controller,SLOT(checkRequiredFields()));
    connect(buttonBox, SIGNAL(rejected()), controller, SLOT(checkChanges()));
    connect(deleteGood, SIGNAL(clicked()), controller, SLOT(removeGoodsFromPositions()));
    connect(priceLevel, SIGNAL(activated(int)), controller, SLOT(initTableModel()));
}

QLineEdit *PriceListView::getName() {
    return name;
}

QTextEdit *PriceListView::getDescribe() {
    return describe;
}

QTextEdit *PriceListView::getContractorData() {
}

QString PriceListView::getSymbol() {
    return "CN";
}
