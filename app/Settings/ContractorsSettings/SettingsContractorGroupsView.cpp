#include "SettingsContractorGroupsView.h"

SettingsContractorGroupsView::SettingsContractorGroupsView(SettingsContractorGroupsController *controller, QWidget *parent) :
        SettingsAbstractItemView(parent)
{
    this->controller = controller;
    initGraphicElements();
    setGraphicSettings();
    setInterfaceController();
}

void SettingsContractorGroupsView::initGraphicElements()
{
    mainLayout->addWidget(new QLabel("Definiowanie, Usuwanie oraz Edycja istniejących grup kontrahenckich:"),1,1,1,6);
    //mainLayout->addWidget(pushRepaint = new Button(ButtonStruct("Odśwież","Odśwież", QSize(100,25))),1,5,1,1);
    mainLayout->addWidget(new QLabel("Grupy: "),3,2,1,1);
    mainLayout->addWidget(boxGroup = new QComboBox(),3,3,1,1);
    mainLayout->addWidget(new QLabel("Nazwa: "),5,2,1,1);
    mainLayout->addWidget(lineName = new QLineEdit(),5,3,1,1);
    mainLayout->addWidget(pushNew = new Button(ButtonStruct("Nowy","Dodawanie nowej grupy", QSize(100,25))),3,5,1,1);
    mainLayout->addWidget(pushEdit = new Button(ButtonStruct("Edytuj","Edycja wybranej grupy", QSize(100,25))),4,5,1,1);
    mainLayout->addWidget(pushDelete = new Button(ButtonStruct("Usun","Usuwanie wybranej grupy", QSize(100,25))),5,5,1,1);
    mainLayout->addWidget(pushSave = new Button(ButtonStruct("Zapisz","Zapisywanie dokonanych zmian", QSize(100,25))),6,5,1,1);
    mainLayout->addItem(new QSpacerItem(0,50,QSizePolicy::Maximum, QSizePolicy::Expanding),7,0,1,7);
}

void SettingsContractorGroupsView::setGraphicSettings()
{
    mainLayout->setColumnMinimumWidth(1,100);
    mainLayout->setColumnMinimumWidth(2,110);
    mainLayout->setRowMinimumHeight(0,25);
    mainLayout->setRowMinimumHeight(2,30);
    mainLayout->setRowMinimumHeight(4,20);
    lineName->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9|_|.| ]{1,60}"),lineName));
}

void SettingsContractorGroupsView::setInterfaceController()
{
    connect(boxGroup,SIGNAL(currentIndexChanged(QString)),controller,SLOT(chooseGroup()));
    connect(pushNew,SIGNAL(clicked()),controller,SLOT(newGroup()));
    connect(pushEdit,SIGNAL(clicked()),controller,SLOT(editGroup()));
    connect(pushDelete,SIGNAL(clicked()),controller,SLOT(deleteGroup()));
    //connect(pushRepaint,SIGNAL(clicked()),controller,SLOT(setModel()));
    connect(pushSave,SIGNAL(clicked()),controller,SLOT(saveGroup()));
}
SettingsContractorGroupsView::~SettingsContractorGroupsView()
{
}

QComboBox *SettingsContractorGroupsView::getBoxGroup() {return boxGroup;}
QLineEdit *SettingsContractorGroupsView::getLineName() {return lineName;}
Button *SettingsContractorGroupsView::getPushSave() {return pushSave;}
Button *SettingsContractorGroupsView::getPushEdit() {return pushEdit;}
Button *SettingsContractorGroupsView::getPushDelete() {return pushDelete;}
Button *SettingsContractorGroupsView::getPushNew() {return pushNew;}
