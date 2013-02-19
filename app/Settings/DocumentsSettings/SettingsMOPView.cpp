#include "SettingsMOPView.h"

SettingsMOPView::SettingsMOPView(SettingsMOPController *controller, QWidget *parent) :
        SettingsAbstractItemView(parent)
{
    this->controller = controller;
    initGraphicElements();
    setGraphicSettings();
    setInterfaceController();
}

void SettingsMOPView::initGraphicElements()
{
    mainLayout->addWidget(new QLabel("Definiowanie, Usuwanie oraz Edycja istniejących sposobów płatności: "),1,1,1,6);
    mainLayout->addWidget(new QLabel("Sposoby płatności: "),3,2,1,1);
    mainLayout->addWidget(boxMOPs = new QComboBox(),3,3,1,1);
    mainLayout->addWidget(new QLabel("Nazwa: "),5,2,1,1);
    mainLayout->addWidget(lineName = new QLineEdit(),5,3,1,1);
    mainLayout->addWidget(new QLabel("Czas trwania (w dniach): "),6,2,1,1);
    mainLayout->addWidget(spinNumberOfDays = new QSpinBox(),6,3,1,1);
    mainLayout->addWidget(pushNew = new Button(ButtonStruct("Nowy","Dodawanie nowej metody płatności", QSize(100,25))),3,5,1,1);
    mainLayout->addWidget(pushEdit = new Button(ButtonStruct("Edytuj","Edycja wybranej metody płatności", QSize(100,25))),4,5,1,1);
    mainLayout->addWidget(pushDelete = new Button(ButtonStruct("Usun","Usuwanie wybranej metody płatności", QSize(100,25))),5,5,1,1);
    mainLayout->addWidget(pushSave = new Button(ButtonStruct("Zapisz","Zapisywanie dokonanych zmian", QSize(100,25))),6,5,1,1);
    mainLayout->addItem(new QSpacerItem(0,50,QSizePolicy::Maximum, QSizePolicy::Expanding),7,0,1,7);
}

void SettingsMOPView::setGraphicSettings()
{
    mainLayout->setColumnMinimumWidth(1,100);
    mainLayout->setColumnMinimumWidth(2,180);
    mainLayout->setRowMinimumHeight(0,25);
    mainLayout->setRowMinimumHeight(2,30);
    spinNumberOfDays->setMaximum(999);
    lineName->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9|_|.| ]{1,35}"),lineName));
}

void SettingsMOPView::setInterfaceController()
{
    connect(boxMOPs,SIGNAL(currentIndexChanged(QString)),controller,SLOT(showMOPs()));
    connect(pushNew,SIGNAL(clicked()),controller,SLOT(addMOP()));
    connect(pushEdit,SIGNAL(clicked()),controller,SLOT(editMOP()));
    connect(pushDelete,SIGNAL(clicked()),controller,SLOT(deleteMOP()));
    connect(pushSave,SIGNAL(clicked()),controller,SLOT(saveMOP()));
}

SettingsMOPView::~SettingsMOPView()
{
}

QLineEdit *SettingsMOPView::getLineName() {return lineName;}
QSpinBox *SettingsMOPView::getSpinNumberOfDays() {return spinNumberOfDays;}
QComboBox *SettingsMOPView::getBoxMOPs() {return boxMOPs;}
Button *SettingsMOPView::getPushSave() {return pushSave;}
Button *SettingsMOPView::getPushEdit() {return pushEdit;}
Button *SettingsMOPView::getPushNew() {return pushNew;}
Button *SettingsMOPView::getPushDelete() {return pushDelete;}
