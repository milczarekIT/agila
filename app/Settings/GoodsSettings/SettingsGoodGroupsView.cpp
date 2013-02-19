#include "SettingsGoodGroupsView.h"

SettingsGoodGroupsView::SettingsGoodGroupsView(SettingsGoodGroupsController *controller, QWidget *parent) :
        SettingsAbstractItemView(parent)
{
    this->controller = controller;
    initGraphicElements();
    setGraphicSettings();
    setInterfaceController();
}

void SettingsGoodGroupsView::initGraphicElements()
{
    mainLayout->addWidget(new QLabel("Definiowanie, Usuwanie oraz Edycja istniejących grup dóbr:"),1,1,1,6);
    mainLayout->addWidget(new QLabel("Grupy: "),3,2,1,1);
    mainLayout->addWidget(boxGroup = new QComboBox(),3,3,1,1);
    mainLayout->addWidget(new QLabel("Nazwa: "),5,2,1,1);
    mainLayout->addWidget(lineName = new QLineEdit(),5,3,1,1);
    mainLayout->addWidget(pushNew = new Button(ButtonStruct("Nowy","Dodawanie nowej grupy", QSize(100,25))),3,5,1,1);
    mainLayout->addWidget(pushEdit = new Button(ButtonStruct("Edytuj","Edycja wybranej grupy", QSize(100,25))),4,5,1,1);
    mainLayout->addWidget(pushDelete = new Button(ButtonStruct("Usun","Usuwanie wybranej grupy", QSize(100,25))),5,5,1,1);
    mainLayout->addWidget(pushSave = new Button(ButtonStruct("Zapisz","Zapisywanie dokonanych zmian", QSize(100,25))),6,5,1,1);
    mainLayout->addItem(new QSpacerItem(0,50,QSizePolicy::Maximum, QSizePolicy::Expanding),7,0,1,7);
    mainLayout->addWidget(tablesInterface = createTablesInterface(),8,1,1,5);
}

void SettingsGoodGroupsView::setGraphicSettings()
{
    mainLayout->setColumnMinimumWidth(1,100);
    mainLayout->setColumnMinimumWidth(2,110);
    mainLayout->setRowMinimumHeight(0,25);
    mainLayout->setRowMinimumHeight(2,30);
    mainLayout->setRowMinimumHeight(4,20);
    mainLayout->setRowMinimumHeight(9,40);
    lineName->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9|_|.| ]{1,60}"),lineName));
}

void SettingsGoodGroupsView::setInterfaceController()
{
    connect(boxGroup,SIGNAL(currentIndexChanged(QString)),controller,SLOT(chooseGroup()));
    connect(pushNew,SIGNAL(clicked()),controller,SLOT(newGroup()));
    connect(pushEdit,SIGNAL(clicked()),controller,SLOT(editGroup()));
    connect(pushDelete,SIGNAL(clicked()),controller,SLOT(deleteGroup()));
    connect(pushSave,SIGNAL(clicked()),controller,SLOT(saveGroup()));
    connect(pushAddFeatures,SIGNAL(clicked()),controller,SLOT(addFeature()));
    connect(pushDelFeatures,SIGNAL(clicked()),controller,SLOT(deleteFeature()));
}

QFrame *SettingsGoodGroupsView::createTablesInterface()
{
    QFrame *widget = new QFrame();
    QGridLayout *layout = new QGridLayout();
    widget->setLayout(layout);
    layout->addWidget(new QLabel("Wybierz cechy dla danej grupy: "),1,1,1,1);
    layout->addWidget(tableGGFeatures = new TableView(),3,1,4,1);
    layout->addWidget(pushAddFeatures = new Button(ButtonStruct("<< Dodaj","Dodaj cechę do danego dobra", QSize(80,25))),4,2,1,1);
    layout->addWidget(pushDelFeatures = new Button(ButtonStruct("Usuń >>","Usuń cechę z danego dobra", QSize(80,25))),5,2,1,1);
    layout->addWidget(tableFeatures = new TableView(),3,3,4,1);
    layout->setRowMinimumHeight(2,10);
    layout->setRowMinimumHeight(7,10);
    widget->setFrameShape(QFrame::Box);
    widget->setFrameShadow(QFrame::Raised);
    return widget;
}

SettingsGoodGroupsView::~SettingsGoodGroupsView()
{
}

QComboBox *SettingsGoodGroupsView::getBoxGroup() {return boxGroup;}
QLineEdit *SettingsGoodGroupsView::getLineName() {return lineName;}
TableView *SettingsGoodGroupsView::getTableFeatures() {return tableFeatures;}
TableView *SettingsGoodGroupsView::getTableGGFeatures() {return tableGGFeatures;}
Button *SettingsGoodGroupsView::getPushSave() {return pushSave;}
Button *SettingsGoodGroupsView::getPushEdit() {return pushEdit;}
Button *SettingsGoodGroupsView::getPushDelete() {return pushDelete;}
Button *SettingsGoodGroupsView::getPushNew() {return pushNew;}
Button *SettingsGoodGroupsView::getPushAddFeatures() {return pushAddFeatures;}
Button *SettingsGoodGroupsView::getPushDelFeatures() {return pushDelFeatures;}
QFrame *SettingsGoodGroupsView::getTablesInterface() {return tablesInterface;}
