#include "GoodsDialogView.h"


GoodsDialogView::GoodsDialogView(QWidget *parent, GoodsDialogController *controller) :
    QDialog(parent)
{
    this->controller = controller;
    lineSymbol = new QLineEdit();
    lineSymbol->setMaxLength(200);
    linePkwiu = new QLineEdit();
    linePriceMagNet = new QLineEdit();
    linePriceMagGross = new QLineEdit();
    lineName = new QLineEdit();
    lineName->setMaxLength(200);
    lineWeight = new QLineEdit();
    radioGood = new QRadioButton();
    radioService = new QRadioButton();
    boxGoodGroup = new QComboBox();
    boxUnit = new QComboBox();
    boxTax = new QComboBox();
    tableFeature = new QTableView();
    picture = new QLabel();
    textDescription = new QTextEdit();
    framePicture = new QFrame();
    addToWarehouseComboBox = new QComboBox();

    createTabWidget();
    createTablePrices();
    createMenu();
    addAllStandardComponents();
    addAllPriceComponents();
    addAllFeatureComponents();
    setTabOrders();
    connect(lineName,SIGNAL(textEdited(QString)),controller,SLOT(nameTyping(QString)));
    connect(lineSymbol,SIGNAL(textEdited(QString)),controller,SLOT(checkAutoSymbol(QString)));

    this->setMaximumSize(650,460);
    this->setMinimumSize(650,460);
}
void GoodsDialogView::setTabOrders()
{
}

GoodsDialogView::~GoodsDialogView()
{
}

void GoodsDialogView::createMenu()
{
    buttonBox = new ButtonBox(this);
    buttonBox->setGeometry(QRect(430,430,200,20));
    context = new QMenu();
    context->addAction("Ustaw zdjęcie");
    context->addAction("Usuń zdjęcie");
    connect (context,SIGNAL(triggered(QAction*)),controller,SLOT(fotoMenuAcces(QAction*)));
    connect (buttonBox, SIGNAL(accepted()), controller,SLOT(checkRequredFields()));
    connect (buttonBox, SIGNAL(rejected()), controller, SLOT(checkChanges()));
}

void GoodsDialogView::createTabWidget()
{
    tabWidget = new QTabWidget(this);
    tabWidget->addTab(tabStandard = new QTabWidget(),"Podstawowe");
    tabWidget->addTab(tabPrices = new QTabWidget(),"Ceny");
    tabWidget->addTab(tabFeatures = new QTabWidget(),"Cechy");
    tabWidget->setGeometry(QRect(5,10,640,410));
    tabStandard->setLayout(standardLayout = new QGridLayout());
    tabPrices->setLayout(pricesLayout = new QGridLayout());
    tabFeatures->setLayout(featuresLayout = new QGridLayout());
    standardLayout->setColumnMinimumWidth(1,220);
    standardLayout->setColumnMinimumWidth(2,170);
    pricesLayout->setColumnMinimumWidth(4,150);
}

void GoodsDialogView::setComponents(QGridLayout *layout,QWidget *widget, QString lineEditValue, int col1,int col2, int col3, int col4)
{
    layout->addWidget(widget,col1,col2,col3,col4);
    if(!lineEditValue.isEmpty())
        layout->addWidget(new QLabel(lineEditValue),col1,col2-1,1,1);
}

void GoodsDialogView::setComponents(QGridLayout *layout,QWidget *widget, int col1,int col2, int col3, int col4)
{
    layout->addWidget(widget,col1,col2,col3,col4);
}

void GoodsDialogView::addAllStandardComponents()
{
    radioGood->setText("Towar");
    radioService->setText("Usługa");

    setComponents(standardLayout,lineSymbol,"<b>Symbol:</b>",1,1,1,2);
    setComponents(standardLayout,lineName,"<b>Nazwa:</b>",2,1,1,2);
    setComponents(standardLayout,radioGood,"",3,1,1,1);
    setComponents(standardLayout,radioService,"",3,2,1,1);
    setComponents(standardLayout,boxUnit,"Jednostka: ",4,1,1,2);
    setComponents(standardLayout,linePkwiu,"PKWiU SWW: ",5,1,1,2);
    setComponents(standardLayout,lineWeight,"Waga: ",6,1,1,2);
    standardLayout->addWidget(picture,0,3,5,3);
    standardLayout->addWidget(framePicture,0,3,5,3);
    setComponents(standardLayout,textDescription,"Opis: ",7,1,5,5);
}

void GoodsDialogView::addWarehouseSelection() {
    addToWarehouseComboBox->addItem("Wszystkie", 0);
    addToWarehouseComboBox->addItem("Aktualny: " + ApplicationManager::getInstance()->getWarehouse()->getName(), ApplicationManager::getInstance()->getWarehouseId());
    setComponents(standardLayout, addToWarehouseComboBox, "Dodaj do magazynu: ", 0, 1, 1, 2);
}

void GoodsDialogView::createTablePrices()
{
    tablePrices = new QTableWidget(3,4);

    tablePrices->setSelectionBehavior(QAbstractItemView::SelectRows);
    tablePrices->setHorizontalHeaderItem(0,new QTableWidgetItem("Netto"));
    tablePrices->setHorizontalHeaderItem(1,new QTableWidgetItem("Brutto"));
    tablePrices->setHorizontalHeaderItem(2,new QTableWidgetItem("Narzut %"));
    tablePrices->setHorizontalHeaderItem(3,new QTableWidgetItem("Upust %"));
    tablePrices->setVerticalHeaderItem(0,new QTableWidgetItem("A"));
    tablePrices->setVerticalHeaderItem(1,new QTableWidgetItem("B"));
    tablePrices->setVerticalHeaderItem(2,new QTableWidgetItem("C"));
    tablePrices->setMaximumHeight(120);
    tablePrices->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tablePrices->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void GoodsDialogView::addAllPriceComponents()
{
    priceValidator = new QRegExpValidator(QRegExp("[0-9]+([.]|,)[0-9]{0,2}"),this);
    setComponents(pricesLayout,tablePrices,2,1,1,4);
    setComponents(pricesLayout,boxTax,"VAT: ",0,1,1,4);
    pricesLayout->addWidget(pushAddTax = new Button(ButtonStruct("+",QSize(25,28))),0,5,1,1);
    pricesLayout->addWidget(pushDeleteTax = new Button(ButtonStruct("-",QSize(25,28))),0,6,1,1);
    setComponents(pricesLayout,linePriceMagNet,"Cena zakupu: ",1,1,1,2);
    linePriceMagNet->setValidator(priceValidator);
    connect(boxTax,SIGNAL(activated(int)),controller,SLOT(calculatePricesForTax(int)));
    connect(linePriceMagNet,SIGNAL(editingFinished()),controller,SLOT(calculateAllPricesFromMag()));
    connect(tablePrices,SIGNAL(itemChanged(QTableWidgetItem*)),controller,SLOT(calculatePrices(QTableWidgetItem*)));

}

void GoodsDialogView::addAllFeatureComponents()
{
    setComponents(featuresLayout,boxGoodGroup,"Grupa dóbr: ",0,1,1,2);
    featuresLayout->addWidget(tableFeature,1,0,3,3);
    connect(boxGoodGroup,SIGNAL(currentIndexChanged(int)),controller,SLOT(updateFeatureModel(int)));
}

void GoodsDialogView::mouseReleaseEvent(QMouseEvent *pEvent)
{
    framePicture->show();
    if ((pEvent->button() == Qt::RightButton) and (tabWidget->currentIndex()==0) and framePicture->underMouse())
    {context->exec(mapToGlobal(pEvent->pos()));
    framePicture->hide();
    }
}

void GoodsDialogView::closeEvent(QCloseEvent *event)
{
     if (event->type() == QEvent::Close) {
         controller->checkChanges();
         event->accept();}
}

void GoodsDialogView::settingsChanged(const QString element)
{
    emit settingsChangedSignal(element);
}

QLineEdit *GoodsDialogView::getLineSymbol() {return lineSymbol;}
QLineEdit *GoodsDialogView::getLineName() {return lineName;}
QLineEdit *GoodsDialogView::getLineTax() {return lineTax;}
QLineEdit *GoodsDialogView::getLinePkwiu() {return linePkwiu;}
QLineEdit *GoodsDialogView::getLinePriceMagNet() {return linePriceMagNet;}
QLineEdit *GoodsDialogView::getLinePriceMagGross() {return linePriceMagGross;}
QLineEdit *GoodsDialogView::getLineWeight() {return lineWeight;}
QRadioButton *GoodsDialogView::getRadioGood() {return radioGood; }
QRadioButton *GoodsDialogView::getRadioService() {return radioService; }
QTextEdit *GoodsDialogView::getTextDescription() {return textDescription;}
QComboBox *GoodsDialogView::getBoxGoodGroup() {return boxGoodGroup;}
QComboBox *GoodsDialogView::getBoxUnit() {return boxUnit;}
QComboBox *GoodsDialogView::getBoxTax() {return boxTax;}
QLabel *GoodsDialogView::getPicture() {return picture;}
QTableView *GoodsDialogView::getTableFeatures(){return tableFeature;}
QTabWidget *GoodsDialogView::getTabWidget(){return tabWidget;}
QComboBox *GoodsDialogView::getAddToWarehouseComboBox() { return addToWarehouseComboBox; }
QTableWidget *GoodsDialogView::getTablePrices(){return this->tablePrices;}
