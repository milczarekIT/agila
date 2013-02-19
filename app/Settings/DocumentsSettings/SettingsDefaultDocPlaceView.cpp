#include "SettingsDefaultDocPlaceView.h"

SettingsDefaultDocPlaceView::SettingsDefaultDocPlaceView(SettingsDefaultDocPlaceController *controller, QWidget *parent) :
        SettingsAbstractItemView(parent)
{
    this->controller = controller;
    initGraphicElements();
    setGraphicSettings();
    setInterfaceController();
}

void SettingsDefaultDocPlaceView::initGraphicElements()
{
    mainLayout->addWidget(new QLabel("Edycja domyślnego miejsca wystawiania dokumentu: "),1,1,1,6);
    mainLayout->addWidget(new QLabel("Miasto: "),3,2,1,1);
    mainLayout->addWidget(defaultDocumentPlace = new QLineEdit(),3,3,1,1);
    mainLayout->addWidget(pushSave = new Button(ButtonStruct("Zapisz","Zapisywanie dokonanych zmian", QSize(100,25))),3,5,1,1);
    mainLayout->addItem(new QSpacerItem(0,50,QSizePolicy::Maximum, QSizePolicy::Expanding),4,0,1,7);
}

void SettingsDefaultDocPlaceView::setGraphicSettings()
{
    mainLayout->setColumnMinimumWidth(1,100);
    mainLayout->setColumnMinimumWidth(2,110);
    mainLayout->setRowMinimumHeight(0,25);
    mainLayout->setRowMinimumHeight(2,20);
    defaultDocumentPlace->setToolTip("Aby dokończyć edycję wciśnij Enter !");
    defaultDocumentPlace->setMaxLength(40);
}

void SettingsDefaultDocPlaceView::setInterfaceController()
{
    connect(defaultDocumentPlace,SIGNAL(returnPressed()),controller,SLOT(defaultDocPlaceChanged()));
    connect(pushSave,SIGNAL(clicked()),controller,SLOT(defaultDocPlaceChanged()));
}

QLineEdit *SettingsDefaultDocPlaceView::getDefaultDocumentPlace() {return defaultDocumentPlace;}
Button *SettingsDefaultDocPlaceView::getPushSave() {return pushSave;}
