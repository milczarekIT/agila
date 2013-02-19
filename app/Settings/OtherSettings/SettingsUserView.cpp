#include "SettingsUserView.h"

SettingsUserView::SettingsUserView(SettingsUserController *controller, QWidget *parent) :
        SettingsAbstractItemView(parent)
{
    this->controller = controller;
    initGraphicElements();
    setGraphicSettings();
    setInterfaceController();
}

void SettingsUserView::initGraphicElements()
{
    mainLayout->addWidget(new QLabel("Edycja danych użytkownika: "),1,1,1,5);
    mainLayout->addWidget(new QLabel("Login: "),3,2,1,1);
    mainLayout->addWidget(new QLabel("Nazwa: "),4,2,1,1);
    mainLayout->addWidget(new QLabel("Zmiana hasła: "),6,1,1,5);
    mainLayout->addWidget(new QLabel("Aktualne hasło: "),8,2,1,1);
    mainLayout->addWidget(new QLabel("Nowe hasło: "),10,2,1,1);
    mainLayout->addWidget(new QLabel("Powtórz: "),11,2,1,1);
    mainLayout->addWidget(label[0] = new QLabel("Definiowanie, usuwanie oraz edycja użytkowników: "),14,1,1,5);
    mainLayout->addWidget(label[1] = new QLabel("Użytkownicy: "),16,2,1,1);
    //mainLayout->addWidget(label[2] = new QLabel("Rodzaj konta: "),17,2,1,1);
    mainLayout->addWidget(lineLogin = new QLineEdit,3,3,1,2);
    mainLayout->addWidget(lineName = new QLineEdit,4,3,1,2);
    mainLayout->addWidget(lineActualPassword = new QLineEdit,8,3,1,2);
    mainLayout->addWidget(lineNewPassword = new QLineEdit,10,3,1,2);
    mainLayout->addWidget(lineReplyNewPassword = new QLineEdit,11,3,1,2);
    mainLayout->addWidget(showSigns = new QCheckBox("Pokaż znaki"),12,3,1,1);
    mainLayout->addWidget(pushSave = new Button(ButtonStruct("Zapisz ","Zapisz dokonane zmiany", QSize(100,25))),12,4,1,1,Qt::AlignRight);
    mainLayout->addWidget(pushAdd = new Button(ButtonStruct(" + ","Dodaj nowego użytkownika", QSize(47,25))),16,4,1,1,Qt::AlignLeft);
    mainLayout->addWidget(pushDelete = new Button(ButtonStruct(" - ","Usuwanie wybranego użytkownika", QSize(47,25))),16,4,1,1,Qt::AlignRight);
    mainLayout->addWidget(boxUsers = new QComboBox(),16,3,1,1);
    //mainLayout->addWidget(boxKindsOfAccount = new QComboBox(),17,3,1,1);
    mainLayout->addItem(new QSpacerItem(0,50,QSizePolicy::Maximum, QSizePolicy::Expanding),18,0,1,7);
}

void SettingsUserView::setGraphicSettings()
{
    mainLayout->setColumnMinimumWidth(1,110);
    mainLayout->setColumnMinimumWidth(2,170);
    mainLayout->setColumnMinimumWidth(3,290);
    mainLayout->setRowMinimumHeight(0,25);
    mainLayout->setRowMinimumHeight(2,20);
    mainLayout->setRowMinimumHeight(5,40);
    mainLayout->setRowMinimumHeight(7,20);
    mainLayout->setRowMinimumHeight(9,15);
    mainLayout->setRowMinimumHeight(13,40);
    mainLayout->setRowMinimumHeight(15,20);
    lineName->setMaxLength(60);
    lineLogin->setMaxLength(20);

    QString toolTip("Hasło powinno składać się wyłącznie z liter, cyfr i spacji");
    lineActualPassword->setToolTip(toolTip);
    lineNewPassword->setToolTip(toolTip);
    lineReplyNewPassword->setToolTip(toolTip);

    //boxKindsOfAccount->addItem("Administrator");
    //boxKindsOfAccount->addItem("Użytkownik");
}

void SettingsUserView::setInterfaceController()
{
    connect(pushSave,SIGNAL(clicked()),controller,SLOT(save()));
    connect(showSigns,SIGNAL(clicked(bool)),controller,SLOT(showSignsInPasswordFields(bool)));
    connect(pushAdd,SIGNAL(clicked()),controller,SLOT(addUser()));
    connect(boxUsers,SIGNAL(currentIndexChanged(int)),controller,SLOT(showUserData(int)));
    connect(pushDelete,SIGNAL(clicked()),controller,SLOT(removeUser()));
}

QLineEdit *SettingsUserView::getLineLogin() {return lineLogin; }
QLineEdit *SettingsUserView::getLineName() {return lineName; }
QLineEdit *SettingsUserView::getLineActualPassword() {return lineActualPassword; }
QLineEdit *SettingsUserView::getLineNewPassword() {return lineNewPassword; }
QLineEdit *SettingsUserView::getLineReplyNewPassword() {return lineReplyNewPassword;}
QCheckBox *SettingsUserView::getShowSigns() {return showSigns;}
Button *SettingsUserView::getPushAdd() { return pushAdd;}
Button *SettingsUserView::getPushDelete() { return pushDelete;}
QComboBox *SettingsUserView::getBoxUsers() {return boxUsers; }
QComboBox *SettingsUserView::getBoxKindsOfAccount() {return boxKindsOfAccount;}
QLabel **SettingsUserView::getLabel() { return label;}
