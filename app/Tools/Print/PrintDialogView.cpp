#include "PrintDialogView.h"

PrintDialogView::PrintDialogView(QWidget *parent, PrintDialogController *controller)
{
    setController(controller);
    setMainLayout(new QGridLayout());
    setPrinterInfo(new QPrinterInfo());
    this->setMinimumSize(520,240);
    this->setLayout(getLayout());
    this->setWindowTitle(controller->getSymbol().append("-Drukowanie dokumentu"));
    initComponents();
    initConnections();
    initTable();
    addData();
    addComponents();
}

void PrintDialogView::initConnections()
{
    connect(browsePath,SIGNAL(clicked()),controller,SLOT(browsePath()));
    connect(buttonCancel,SIGNAL(clicked()),this,SLOT(reject()));
    connect(buttonPrint,SIGNAL(clicked()),this,SLOT(accept()));
    connect(buttonPreview,SIGNAL(clicked()),controller,SLOT(printPreview()));
    connect(boxPrinter,SIGNAL(currentIndexChanged(QString)),controller,SLOT(printerChooser(QString)));
}

void PrintDialogView::initComponents()
{
    linePath = new QLineEdit();
    boxPrint = new QComboBox();
    checkBox= new QCheckBox("Ustaw ścieżkę jako domyślną");
    checkDuplicate = new QCheckBox("Drukuj jako duplikat");
    boxPrinter = new QComboBox();
    boxCopies = new QSpinBox();
    buttonPreview = new Button(ButtonStruct("Podgląd",QSize(100,28)));
    buttonPrint = new Button(ButtonStruct("Drukuj",QSize(100,28)));
    buttonCancel = new Button(ButtonStruct("Anuluj",QSize(100,28)));
    browsePath = new Button(ButtonStruct("Zmień",QSize(100,28)));
}

void PrintDialogView::addData()
{
    boxPrint->addItem("Drukowanie dokumentu + zapis do pdf");
    boxPrint->addItem("Drukowanie dokumentu");
    boxPrint->addItem("Zapis do pdf");
    boxCopies->setMinimum(1);
    boxCopies->setMaximum(100);
    linePath->setText(controller->getPrinter()->outputFileName());
    linePath->setText(controller->getPrinter()->outputFileName());
    int indexOfDefaultPrinter=0;
    QList<QPrinterInfo> available= getPrinterInfo()->availablePrinters();
    for (int i=0; i<available.size();i++)
    {
        if(available.at(i).isDefault())
            indexOfDefaultPrinter=i;
      boxPrinter->addItem(available.at(i).printerName());
    }
    boxPrinter->setCurrentIndex(indexOfDefaultPrinter);
    checkBox->setChecked(false);
    checkDuplicate->setChecked(false);
}
void PrintDialogView::initTable()
{
    table = new QTableWidget();
    table->setColumnCount(2);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setColumnWidth(0,390);
    table->setColumnWidth(1,265);
    table->setHorizontalHeaderItem(0,new QTableWidgetItem("Nazwa"));
    table->setHorizontalHeaderItem(1,new QTableWidgetItem("Data Wystawienia"));
}

void PrintDialogView::addComponents()
{
    mainLayout->addWidget(new QLabel("Drukarka: "),0,0);
    mainLayout->addWidget(boxPrinter,0,1);
    mainLayout->addWidget(new QLabel("Czynności: "),0,2);
    mainLayout->addWidget(boxPrint,0,3);
    mainLayout->addWidget(buttonPreview,0,4);
    mainLayout->addWidget(new QLabel("Zapisz w:"),1,0);
    mainLayout->addWidget(linePath,1,1,1,3);
    mainLayout->addWidget(browsePath,1,4);
    mainLayout->addWidget(checkBox,2,0,1,2);
    mainLayout->addWidget(checkDuplicate,2,3,1,2);
    mainLayout->addWidget(new QLabel("Drukuj dokumenty powiązane"),3,0,1,2);
    mainLayout->addWidget(table,4,0,3,4);
    mainLayout->addWidget(buttonCancel,7,3,Qt::AlignRight);
    mainLayout->addWidget(buttonPrint,7,4);
    mainLayout->addWidget(new QLabel("Ilość kopi: "),7,0,Qt::AlignLeft);
    mainLayout->addWidget(boxCopies,7,1,Qt::AlignLeft);
}

QLineEdit *PrintDialogView::getPath()
{
    return this->linePath;
}

QSpinBox* PrintDialogView::getSpinBox()
{
    return this->boxCopies;
}

QComboBox* PrintDialogView::getBoxPrint()
{
    return this->boxPrint;
}
QTableWidget* PrintDialogView::getTable()
{
    return this->table;
}

PrintDialogView::~PrintDialogView()
{
    delete inf;
    delete mainLayout;
}
bool PrintDialogView::ifSetAsDefualtPath()
{
    return this->checkBox->isChecked();
}
bool PrintDialogView::isDuplicate()
{
    return this->checkDuplicate->isChecked();
}

PrintDialogController* PrintDialogView::getController(){return controller;}
void PrintDialogView::setController(PrintDialogController* controller){this->controller=controller;}
QGridLayout* PrintDialogView::getLayout(){return mainLayout;}
void PrintDialogView::setMainLayout(QGridLayout* layout){this->mainLayout=layout;}
void PrintDialogView::setPrinterInfo(QPrinterInfo* info){this->inf=info;}
QPrinterInfo * PrintDialogView::getPrinterInfo(){return inf;}
