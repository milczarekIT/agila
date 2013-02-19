#include "SettingsFeaturesView.h"

SettingsFeaturesView::SettingsFeaturesView(SettingsFeaturesController *controller, QWidget *parent) :
        SettingsAbstractItemView(parent)
{
    this->controller = controller;
    initGraphicElements();
    setGraphicSettings();
    setInterfaceController();
}
void SettingsFeaturesView::initGraphicElements()
{
    mainLayout->addWidget(new QLabel("Definiowanie, Usuwanie oraz Edycja istniejących cech towarowych: "),1,1,1,6);
    mainLayout->addWidget(new QLabel("Jednostki: "),3,2,1,1);
    mainLayout->addWidget(boxFeatures = new QComboBox(),3,3,1,1);
    mainLayout->addWidget(new QLabel("Nazwa: "),5,2,1,1);
    mainLayout->addWidget(lineName = new QLineEdit(),5,3,1,1);
    mainLayout->addWidget(pushNew = new Button(ButtonStruct("Nowy","Dodawanie nowej cechy", QSize(100,25))),3,5,1,1);
    mainLayout->addWidget(pushEdit = new Button(ButtonStruct("Edytuj","Edycja wybranej cechy", QSize(100,25))),4,5,1,1);
    mainLayout->addWidget(pushDelete = new Button(ButtonStruct("Usun","Usuwanie wybranej cechy", QSize(100,25))),5,5,1,1);
    mainLayout->addWidget(pushSave = new Button(ButtonStruct("Zapisz","Zapisywanie dokonanych zmian", QSize(100,25))),6,5,1,1);
    mainLayout->addItem(new QSpacerItem(0,50,QSizePolicy::Maximum, QSizePolicy::Expanding),7,0,1,7);
}

void SettingsFeaturesView::setGraphicSettings()
{
    mainLayout->setColumnMinimumWidth(1,100);
    mainLayout->setColumnMinimumWidth(2,110);
    mainLayout->setRowMinimumHeight(0,25);
    mainLayout->setRowMinimumHeight(2,30);
    lineName->setMaxLength(60);
}

void SettingsFeaturesView::setInterfaceController()
{
    connect(boxFeatures,SIGNAL(currentIndexChanged(QString)),controller,SLOT(showFeatures()));
    connect(pushNew,SIGNAL(clicked()),controller,SLOT(addFeature()));
    connect(pushEdit,SIGNAL(clicked()),controller,SLOT(editFeature()));
    connect(pushDelete,SIGNAL(clicked()),controller,SLOT(deleteFeature()));
    connect(pushSave,SIGNAL(clicked()),controller,SLOT(saveFeature()));
}

SettingsFeaturesView::~SettingsFeaturesView()
{
}

QLineEdit *SettingsFeaturesView::getLineName() {return lineName;}
QComboBox *SettingsFeaturesView::getBoxFeatures() {return boxFeatures;}
Button *SettingsFeaturesView::getPushSave() {return pushSave;}
Button *SettingsFeaturesView::getPushEdit() {return pushEdit;}
Button *SettingsFeaturesView::getPushNew() {return pushNew;}
Button *SettingsFeaturesView::getPushDelete() {return pushDelete;}
