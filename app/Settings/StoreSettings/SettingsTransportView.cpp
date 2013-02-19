#include "SettingsTransportView.h"

SettingsTransportView::SettingsTransportView(SettingsTransportController *controller, QWidget *parent) :
        SettingsAbstractItemView(parent)
{
    this->controller = controller;
    initGraphicElements();
    setGraphicSettings();
    setInterfaceController();
}
void SettingsTransportView::initGraphicElements()
{
    mainLayout->addWidget(new QLabel("Definiowanie, Usuwanie oraz Edycja istniejących rodzajów transportu: "),1,1,1,6);
    mainLayout->addWidget(new QLabel("Rodzaje transportów: "),3,2,1,1);
    mainLayout->addWidget(boxTransports = new QComboBox(),3,3,1,1);
    mainLayout->addWidget(new QLabel("Nazwa: "),5,2,1,1);
    mainLayout->addWidget(lineName = new QLineEdit(),5,3,1,1);
    mainLayout->addWidget(pushNew = new Button(ButtonStruct("Nowy","Dodawanie nowego rodzaju transportu", QSize(100,25))),3,5,1,1);
    mainLayout->addWidget(pushEdit = new Button(ButtonStruct("Edytuj","Edycja wybranego rodzaju transportu", QSize(100,25))),4,5,1,1);
    mainLayout->addWidget(pushDelete = new Button(ButtonStruct("Usun","Usuwanie wybranego transportu", QSize(100,25))),5,5,1,1);
    mainLayout->addWidget(pushSave = new Button(ButtonStruct("Zapisz","Zapisywanie dokonanych zmian", QSize(100,25))),6,5,1,1);
    mainLayout->addItem(new QSpacerItem(0,50,QSizePolicy::Maximum, QSizePolicy::Expanding),7,0,1,7);
}

void SettingsTransportView::setGraphicSettings()
{
    mainLayout->setColumnMinimumWidth(1,100);
    mainLayout->setColumnMinimumWidth(2,110);
    mainLayout->setRowMinimumHeight(0,25);
    mainLayout->setRowMinimumHeight(2,30);
    lineName->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9|_|.| ]{1,40}"),lineName));
}

void SettingsTransportView::setInterfaceController()
{
    connect(boxTransports,SIGNAL(currentIndexChanged(QString)),controller,SLOT(showTransports()));
    connect(pushNew,SIGNAL(clicked()),controller,SLOT(addTransport()));
    connect(pushEdit,SIGNAL(clicked()),controller,SLOT(editTransport()));
    connect(pushDelete,SIGNAL(clicked()),controller,SLOT(deleteTransport()));
    connect(pushSave,SIGNAL(clicked()),controller,SLOT(saveTransport()));
}

SettingsTransportView::~SettingsTransportView()
{
}

QLineEdit *SettingsTransportView::getLineName() {return lineName;}
QComboBox *SettingsTransportView::getBoxTransports() {return boxTransports;}
Button *SettingsTransportView::getPushSave() {return pushSave;}
Button *SettingsTransportView::getPushEdit() {return pushEdit;}
Button *SettingsTransportView::getPushNew() {return pushNew;}
Button *SettingsTransportView::getPushDelete() {return pushDelete;}
