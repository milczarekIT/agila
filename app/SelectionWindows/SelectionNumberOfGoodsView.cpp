#include "SelectionNumberOfGoodsView.h"

SelectionNumberOfGoodsView::SelectionNumberOfGoodsView(SelectionNumberOfGoodsController*controller,QWidget *parent) :
    QDialog(parent)
{
    this->controller=controller;
    initLabels();
    initLineEdits();
    initButtons();
    initConnections();
    addAllComponents();
    setPrice();
}

void SelectionNumberOfGoodsView::addAllComponents() {
    this->setWindowTitle(trUtf8("Ilość"));

    QGridLayout* mainLayout = new QGridLayout();
    this->setLayout(mainLayout);
    checkQuantity->setChecked(true);
    mainLayout->addWidget(checkQuantity, 0, 0);
    mainLayout->addWidget(spinboxNumberOfGoods, 0, 2);
    mainLayout->addWidget(labelUnitQuantity, 0,1,Qt::AlignLeft);

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
    {
        mainLayout->addWidget(checkMaxQuantity,1,0);
        mainLayout->addWidget(lineEditMaxQuantity,1,2);
        mainLayout->addWidget(labelUnitQuantityMax, 1,1,Qt::AlignLeft);
    }

    mainLayout->addWidget(labelLevelOfPrices,2,0);
    mainLayout->addWidget(boxLevelOfPrices,2,2);
    mainLayout->addWidget(new QLabel("Cenna netto:"),3,0);
    mainLayout->addWidget(new QLabel("Cenna brutto:"),4,0);
    mainLayout->addWidget(labelPriceNet,3,2);
    mainLayout->addWidget(labelPriceGross,4,2);
    mainLayout->addWidget(buttonBox, 5, 2);
}


void SelectionNumberOfGoodsView::initLabels()   {
    labelUnitQuantity = new QLabel("");

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
        labelUnitQuantityMax = new QLabel("");

    labelPriceNet = new QLabel("");
    labelPriceGross = new QLabel("");
    labelLevelOfPrices = new QLabel("Poziom cen:");

}

void SelectionNumberOfGoodsView::initLineEdits()    {
    spinboxNumberOfGoods = new QDoubleSpinBox();
    spinboxNumberOfGoods->setAlignment(Qt::AlignRight);
    spinboxNumberOfGoods->setValue(1.0);
    checkQuantity = new QRadioButton("Ilość");
    checkQuantity->setFocusPolicy(Qt::NoFocus);

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
    {
        checkMaxQuantity = new QRadioButton("Maksymalna dostępna ilość");
        lineEditMaxQuantity = new QLineEdit();
        checkMaxQuantity->setFocusPolicy(Qt::NoFocus);
    }

    boxLevelOfPrices = new QComboBox();
    boxLevelOfPrices->addItem("A", Price::A);
    boxLevelOfPrices->addItem("B", Price::B);
    boxLevelOfPrices->addItem("C", Price::C);    
}

void SelectionNumberOfGoodsView::initButtons()  {
    buttonBox = new ButtonBox(this);
}

void SelectionNumberOfGoodsView::initConnections()  {
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(boxLevelOfPrices,SIGNAL(currentIndexChanged(int)),this,SLOT(setPrice(int)));
}

void SelectionNumberOfGoodsView::setMaxNumberOfGoods(double max) {
    if(max >= 0.0)  {
        spinboxNumberOfGoods->setMaximum(max);

        if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
            lineEditMaxQuantity->setText(QVariant(max).toString());
    }
    else
    {
        spinboxNumberOfGoods->setValue(0.0);

        if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
            lineEditMaxQuantity->setText("Brak");
    }
}

void SelectionNumberOfGoodsView::setUnitName(QString unitName)  {
    labelUnitQuantity->setText("["+unitName+"]");

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
        labelUnitQuantityMax->setText("["+unitName+"]");
}


void SelectionNumberOfGoodsView::setZeroPlaces(int zeroPlaces)  {
    spinboxNumberOfGoods->setDecimals(zeroPlaces);
}

QComboBox *SelectionNumberOfGoodsView::getComoboBox(){return boxLevelOfPrices;}

void SelectionNumberOfGoodsView::setPrice(int index)
{
    if(!(controller->getSymbol().contains("WZ")||controller->getSymbol().contains("PZ")||controller->getSymbol().contains("ZD")
        ||controller->getSymbol().contains("RW")||controller->getSymbol().contains("PW")||controller->getSymbol().contains("MM")))
    {
       if(index==0)
        {
           this->setPrices(controller->getGood()->getPriceNet(Price::A).toString(),controller->getGood()->getPriceGross(Price::A).toString());
        }
       else if(index==1)
        {
           this->setPrices(controller->getGood()->getPriceNet(Price::B).toString(),controller->getGood()->getPriceGross(Price::B).toString());
        }
       else if(index==2)
        {
           this->setPrices(controller->getGood()->getPriceNet(Price::C).toString(),controller->getGood()->getPriceGross(Price::C).toString());
        }
    }
    else
    {
        this->setPrices(controller->getGood()->getPriceNet(Price::MAG).toString(),controller->getGood()->getPriceGross(Price::MAG).toString());
        this->boxLevelOfPrices->hide();
        this->labelLevelOfPrices->hide();
    }
}

void SelectionNumberOfGoodsView::setPrices(QString priceNet,QString priceGross)
{
    this->labelPriceNet->setText(priceNet);
    this->labelPriceGross->setText(priceGross);
}

double SelectionNumberOfGoodsView::getPriceNet()
{
    return this->labelPriceNet->text().toDouble();
}

double SelectionNumberOfGoodsView::getPriceGross()
{
    return this->labelPriceGross->text().toDouble();
}

bool SelectionNumberOfGoodsView::isCheckMaxQuantity()
{
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
        return this->checkMaxQuantity->isChecked();
    else
        return false;
}

bool SelectionNumberOfGoodsView::isCheckQuantity()
{
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
        return this->checkQuantity->isChecked();
    else
        return true;
}

double SelectionNumberOfGoodsView::getQuantity()
{
    return this->spinboxNumberOfGoods->value();
}

double SelectionNumberOfGoodsView::getMaxQuantity()
{
    return this->lineEditMaxQuantity->text().toDouble();
}

int SelectionNumberOfGoodsView::getSelectedPriceLevel() {
    int index = this->boxLevelOfPrices->currentIndex();
    return this->boxLevelOfPrices->itemData(index).toInt();
}
