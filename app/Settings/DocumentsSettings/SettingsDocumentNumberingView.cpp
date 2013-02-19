#include "SettingsDocumentNumberingView.h"

SettingsDocumentNumberingView::SettingsDocumentNumberingView(SettingsDocumentNumberingController *controller, QWidget *parent) :
        SettingsAbstractItemView(parent)
{
    this->controller = controller;
    initGraphicElements();
    setGraphicSettings();
    setInterfaceController();
}

void SettingsDocumentNumberingView::initGraphicElements()
{
    mainLayout->addWidget(new QLabel("Edycja sposobów numerowania dokumentów: "),1,1,1,3);
    mainLayout->addWidget(new QLabel("Grupa dokumentów:"),3,1,1,2);
    mainLayout->addWidget(whichModule = new QComboBox(),3,3,1,4);
    mainLayout->addWidget(new QLabel("Numeracje dokumentów: "),4,1,1,2);
    mainLayout->addWidget(kindsOfNumbering = new QComboBox(),4,3,1,4);
    mainLayout->addWidget(new QLabel("Forma:"),5,1,1,2);
    mainLayout->addWidget(numberingDocument = new QLineEdit(),5,3,1,1);
    mainLayout->addWidget(new QLabel("/"),5,4,1,1);
    mainLayout->addWidget(numberingRest = new QLineEdit(),5,5,1,2);
    mainLayout->addWidget(pushSave = new Button(ButtonStruct("Zapisz","Zapisywanie dokonywanych zmian. ", QSize(100,25))),6,6,1,1);
    mainLayout->addWidget(createTablesInterface(),8,2,1,4);
    mainLayout->addItem(new QSpacerItem(0,50,QSizePolicy::Maximum, QSizePolicy::Expanding),9,1,1,4);
}

void SettingsDocumentNumberingView::setGraphicSettings()
{
    mainLayout->setColumnMinimumWidth(0,8);
    mainLayout->setColumnMinimumWidth(1,100);
    mainLayout->setColumnMinimumWidth(2,160);
    mainLayout->setColumnMinimumWidth(5,230);
    mainLayout->setColumnMinimumWidth(6,100);
    mainLayout->setColumnMinimumWidth(7,8);
    mainLayout->setRowMinimumHeight(0,27);
    mainLayout->setRowMinimumHeight(2,27);
    mainLayout->setRowMinimumHeight(7,50);
    mainLayout->setRowMinimumHeight(8,105);

    numberingDocument->setEnabled(false);
    numberingRest->setEnabled(false);
    sign->setText("Znak specjalny");
    sign->setStatusTip("Wciśnij enter aby wprowadzić");

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Sale))
        whichModule->addItem("Sprzedaży");
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Purchase))
        whichModule->addItem("Zakupu");
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Cash))
        whichModule->addItem("Kasowych");
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Order))
        whichModule->addItem("Zamówień");
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
        whichModule->addItem("Magazynowych");

    createEditorButton(month);
    createEditorButton(day);
    createEditorButton(numbering);
    createEditorButton(year);
}

void SettingsDocumentNumberingView::setInterfaceController()
{
    connect(sign,SIGNAL(selectionChanged()),controller,SLOT(clickedLineNumbering()));
    connect(sign,SIGNAL(returnPressed()),controller,SLOT(releaseLineNumbering()));
    connect(pushSave,SIGNAL(clicked()),controller,SLOT(showDocumentNumbering()));
    connect(year,SIGNAL(clicked()),controller,SLOT(actionYear()));
    connect(month,SIGNAL(clicked()),controller,SLOT(actionMonth()));
    connect(day,SIGNAL(clicked()),controller,SLOT(actionDay()));
    connect(numbering,SIGNAL(clicked()),controller,SLOT(actionNumbering()));
    connect(kindsOfNumbering,SIGNAL(activated(QString)),controller,SLOT(showDocumentNumbering()));
    connect(whichModule,SIGNAL(currentIndexChanged(int)),controller,SLOT(setWhichSymbols()));
}

QFrame *SettingsDocumentNumberingView::createTablesInterface()
{
    QFrame *widget = new QFrame();
    QGridLayout *layout = new QGridLayout();
    widget->setLayout(layout);

    layout->addWidget(month = new Button(ButtonStruct("Miesiąc","Dodanie znacznika miesiąca", QSize(250,25))),0,2,1,1);
    layout->addWidget(day = new Button(ButtonStruct("Dzień","Dodanie znacznika dnia", QSize(250,25))),0,1,1,1);
    layout->addWidget(year = new Button(ButtonStruct("Rok","Dodanie znacznika roku", QSize(250,25))),1,1,1,1);
    layout->addWidget(numbering = new Button(ButtonStruct("Numeracja","Dodanie znacznika numeracji", QSize(250,25))),1,2,1,1);
    layout->addWidget(sign = new QLineEdit(),2,1,1,2);

    sign->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9]*"),sign));
    widget->setFrameShape(QFrame::Box);
    widget->setFrameShadow(QFrame::Raised);
    widget->setProperty("whiteRoundFrame",true);
    return widget;
}

void SettingsDocumentNumberingView::createEditorButton(QPushButton *button)
{
    button->setCheckable(true);
    button->setFlat(true);
}

QLineEdit *SettingsDocumentNumberingView::getSign() {return sign;}
QComboBox *SettingsDocumentNumberingView::getWhichModule(){return whichModule;}
QComboBox *SettingsDocumentNumberingView::getKindsOfNumbering() {return kindsOfNumbering;}
QLineEdit *SettingsDocumentNumberingView::getNumberingDocument() {return numberingDocument;}
QLineEdit *SettingsDocumentNumberingView::getNumberingRest() {return numberingRest;}
Button *SettingsDocumentNumberingView::getYear() {return year;}
Button *SettingsDocumentNumberingView::getMonth() {return month;}
Button *SettingsDocumentNumberingView::getDay() {return day;}
Button *SettingsDocumentNumberingView::getNumbering() {return numbering;}
Button *SettingsDocumentNumberingView::getPushSave() {return pushSave;}

