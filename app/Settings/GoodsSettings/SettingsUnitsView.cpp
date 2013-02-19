#include "SettingsUnitsView.h"

SettingsUnitsView::SettingsUnitsView(SettingsUnitsController *controller, QWidget *parent) :
    SettingsAbstractItemView(parent)
{
    this->controller = controller;
    initGraphicElements();
    setGraphicSettings();
    setInterfaceController();
}

void SettingsUnitsView::initGraphicElements()
{
    mainLayout->addWidget(new QLabel("Definiowanie, Usuwanie oraz Edycja istniejących jednostek miary: "),1,1,1,6);
    mainLayout->addWidget(new QLabel("Jednostki: "),3,2,1,1);
    mainLayout->addWidget(boxUnits = new QComboBox(),3,3,1,1);
    mainLayout->addWidget(new QLabel("Nazwa: "),5,2,1,1);
    mainLayout->addWidget(lineName = new QLineEdit(),5,3,1,1);
    mainLayout->addWidget(new QLabel("Ilość miejsc po przecinku: "),6,2,1,1);
    mainLayout->addWidget(spinZeroPlaces = new QSpinBox(),6,3,1,1);
    mainLayout->addWidget(pushNew = new Button(ButtonStruct("Nowy","Dodawanie nowej jednostki", QSize(100,25))),3,5,1,1);
    mainLayout->addWidget(pushEdit = new Button(ButtonStruct("Edytuj","Edycja wybranej jednostki", QSize(100,25))),4,5,1,1);
    mainLayout->addWidget(pushDelete = new Button(ButtonStruct("Usun","Usuwanie wybranej jednostki", QSize(100,25))),5,5,1,1);
    mainLayout->addWidget(pushSave = new Button(ButtonStruct("Zapisz","Zapisywanie dokonanych zmian", QSize(100,25))),6,5,1,1);
    mainLayout->addItem(new QSpacerItem(0,50,QSizePolicy::Maximum, QSizePolicy::Expanding),7,0,1,7);
}

void SettingsUnitsView::setGraphicSettings()
{
    mainLayout->setColumnMinimumWidth(1,100);
    mainLayout->setColumnMinimumWidth(2,180);
    mainLayout->setRowMinimumHeight(0,25);
    mainLayout->setRowMinimumHeight(2,30);
    spinZeroPlaces->setMaximum(3);
    lineName->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z|.]{1,5}"),lineName));
}

void SettingsUnitsView::setInterfaceController()
{
    connect(boxUnits,SIGNAL(currentIndexChanged(QString)),controller,SLOT(showUnit()));
    connect(pushNew,SIGNAL(clicked()),controller,SLOT(addUnit()));
    connect(pushEdit,SIGNAL(clicked()),controller,SLOT(editUnit()));
    connect(pushDelete,SIGNAL(clicked()),controller,SLOT(deleteUnit()));
    connect(pushSave,SIGNAL(clicked()),controller,SLOT(saveUnit()));
}

SettingsUnitsView::~SettingsUnitsView()
{
}

QLineEdit *SettingsUnitsView::getLineName() {return lineName;}
QSpinBox *SettingsUnitsView::getSpinZeroPlaces() {return spinZeroPlaces;}
QComboBox *SettingsUnitsView::getBoxUnits() {return boxUnits;}
Button *SettingsUnitsView::getPushSave() {return pushSave;}
Button *SettingsUnitsView::getPushEdit() {return pushEdit;}
Button *SettingsUnitsView::getPushNew() {return pushNew;}
Button *SettingsUnitsView::getPushDelete() {return pushDelete;}
