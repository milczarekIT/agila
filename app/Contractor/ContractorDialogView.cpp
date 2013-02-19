#include "ContractorDialogView.h"

ContractorDialogView::ContractorDialogView(QWidget *parent,ContractorDialogController *controller) :
    QDialog(parent)
{
     this->controller=controller;
     lineName = new QLineEdit;
     lineName->setMaxLength(70); // jesli indywidualny to dowzolone właściwie 255
     textCompany = new QLineEdit;
     linePostCode = new QLineEdit;
     linePostCode->setMaxLength(6);
     lineCity = new QLineEdit;
     lineCity->setMaxLength(40);
     lineAdress = new QLineEdit;
     lineAdress->setMaxLength(60);
     lineTIN = new QLineEdit;
     lineRegon = new QLineEdit;
     lineAccount = new QLineEdit;
     lineWebsite = new QLineEdit;
     lineWebsite->setMaxLength(60);
     lineEmail = new QLineEdit;
     lineEmail->setMaxLength(60);
     lineDiscount = new QLineEdit;
     lineAdditional = new QLineEdit;
     lineAdditional->setMaxLength(60);
     phones = new QTableView;
     lineSymbol = new QLineEdit;
     boxConGroup = new QComboBox;
     boxSOM = new QComboBox;
     boxAdditionalId = new QComboBox;
     textComments = new QTextEdit;
     radioBusiness = new QRadioButton;
     radioIndividual = new QRadioButton;
     checkBoxSupplier = new QCheckBox;
     checkBoxBuyer = new QCheckBox;
     labelName = new QLabel;
     labelCompany = new QLabel;
     labelTIN = new QLabel;

     createTabWidget();
     addAllStandardComponents();
     addAllAdditionalComponents();
     createMenu();
     connect(lineSymbol,SIGNAL(textEdited(QString)),controller,SLOT(checkAutoSymbol(QString)));
     connect(linePostCode, SIGNAL(editingFinished()), controller, SLOT(autoPostalCode()));

     this->setMaximumSize(650,500);
     this->setMinimumSize(650,500);
}

ContractorDialogView::~ContractorDialogView()
{
    delete standardLayout;
    delete additionalLayout;
}

void ContractorDialogView::createTabWidget()
{
    tabWidget = new QTabWidget(this);
    tabWidget->addTab(tabStandard = new QTabWidget(),"Podstawowe");
    tabWidget->addTab(tabAdditional = new QTabWidget(),"Dodatkowe");
    tabWidget->setGeometry(QRect(5,10,640,450));
    tabStandard->setLayout(standardLayout = new QGridLayout());
    tabAdditional->setLayout(additionalLayout = new QGridLayout());
    standardLayout->setColumnMinimumWidth(4,170);
}

void ContractorDialogView::createMenu()
{
    buttonBox = new ButtonBox(this);
    buttonBox->setGeometry(QRect(430,470,200,20));
    connect(buttonBox, SIGNAL(accepted()), controller, SLOT(checkRequiredFields()));
    connect(buttonBox, SIGNAL(rejected()), controller, SLOT(checkChanges()));
}

void ContractorDialogView::closeEvent(QCloseEvent *event)
 {
     if (event->type() == QEvent::Close) {
         controller->checkChanges();
         event->accept();}
 }

void ContractorDialogView::setComponents(QGridLayout *layout, QWidget *widget, QString labelValue, int col1,int col2, int col3, int col4)
{
    layout->addWidget(widget,col1,col2,col3,col4);
    layout->addWidget(new QLabel(labelValue),col1,col2-1,1,1);
}

void ContractorDialogView::setComponents(QGridLayout *layout, QWidget *widget, QLabel *label, int col1,int col2, int col3, int col4)
{
    layout->addWidget(widget,col1,col2,col3,col4);
    layout->addWidget(label,col1,col2-1,1,1);
}

void ContractorDialogView::addAllStandardComponents()
{
    setComponents(standardLayout,lineSymbol,"<b>Symbol:</b>",0,1,1,6);
    setComponents(standardLayout,radioBusiness,"",1,1,1,1);
    setComponents(standardLayout,radioIndividual,"",1,4,1,1);
    setComponents(standardLayout,checkBoxSupplier,"",2,1,1,1);
    setComponents(standardLayout,checkBoxBuyer,"",2,4,1,1);
    setComponents(standardLayout,textCompany,labelCompany, 3,1,1,6);
    setComponents(standardLayout,lineName, labelName, 4,1,1,6);
    setComponents(standardLayout,boxConGroup,"Gr. kontrahencka: ",5,1,1,4);
    setComponents(standardLayout,linePostCode,"<b>Kod pocztowy:</b>",6,1,1,1);
    setComponents(standardLayout,lineCity,"<b>Miasto:</b>",6,3,1,4);
    setComponents(standardLayout,lineAdress,"<b>Adres:</b>",7,1,1,6);
    setComponents(standardLayout,lineTIN,labelTIN,9,1,1,2);
    // dozwolone formaty wprowadzania (zamiast myślników można używać spacji): 0123456789, 012-345-67-89, 012-34-567-89, 012-34-56-789
    lineTIN->setValidator(new QRegExpValidator(QRegExp("([0-9]{10})|([0-9]{3}[ -]{1}[0-9]{3}[ -]{1}[0-9]{2}[ -]{1}[0-9]{2})|([0-9]{3}[ -]{1}[0-9]{2}[ -]{1}[0-9]{3}[ -]{1}[0-9]{2})|([0-9]{3}[ -]{1}[0-9]{2}[ -]{1}[0-9]{2}[ -]{1}[0-9]{3})"), this));    setComponents(standardLayout,boxAdditionalId,"",9,6,1,1);
    setComponents(standardLayout,lineRegon,"",9,4,1,2);
    setComponents(standardLayout,lineAccount,"Numer konta: ",10,1,1,6);
    lineAccount->setInputMask("99 9999 9999 9999 9999 9999 9999");

    standardLayout->addWidget(new QLabel("Numery telefonu"),13,0);
    standardLayout->addWidget(buttonAddPhone = new Button(ButtonStruct("Dodaj",QSize(100,28))),14,0);
    standardLayout->addWidget(buttonRemovePhone = new Button(ButtonStruct("Usuń",QSize(100,28))),15,0);
    standardLayout->addWidget(phones = new QTableView(),13,1,4,6);
    standardLayout->addWidget(buttonAddGroup = new Button(ButtonStruct("+",QSize(50,28))),5,5,1,1);
    standardLayout->addWidget(buttonRemoveGroup = new Button(ButtonStruct("-",QSize(50,28))),5,6,1,1);
    standardLayout->addWidget(line = new QFrame(),8,0,1,7);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    buttonAddGroup->setMaximumWidth(40);
    buttonRemoveGroup->setMaximumWidth(40);
    connect (buttonAddPhone,SIGNAL(clicked()),controller,SLOT(addPhone()));
    connect (buttonRemovePhone,SIGNAL(clicked()),controller,SLOT(removePhone()));
    connect(buttonAddGroup,SIGNAL(clicked()),controller,SLOT(addContractorGroup()));
    connect(buttonRemoveGroup,SIGNAL(clicked()),controller,SLOT(removeContractorGroup()));
    connect(radioBusiness, SIGNAL(toggled(bool)), controller, SLOT(selectedBusinessContractor(bool)));
    connect(radioIndividual, SIGNAL(toggled(bool)), controller, SLOT(selectedIndividualContractor(bool)));

    radioBusiness->setText("Firma");
    radioIndividual->setText("Osoba fizyczna");
    checkBoxSupplier->setText("Dostawca");
    checkBoxBuyer->setText("Nabywca");
}

void ContractorDialogView::addAllAdditionalComponents()
{
    setComponents(additionalLayout,lineDiscount,"Rabat: ",0,1,1,2);
    additionalLayout->addWidget(new QLabel("%"),0,3,1,1);
    lineDiscount->setValidator(new QRegExpValidator(QRegExp("[0-9]{0,2}([.]|,)[0-9]{0,2}"),lineDiscount));
    setComponents(additionalLayout,lineEmail,"eMail:",1,1,1,6);
    setComponents(additionalLayout,lineWebsite,"Strona internetowa: ",2,1,1,6);
    setComponents(additionalLayout,textComments,"Komentarz: ",3,1,1,6);
    setComponents(additionalLayout,boxSOM,"Skąd o nas wiesz: ",4,1,1,4);
    setComponents(additionalLayout,lineAdditional,"Dodatkowe: ",5,1,1,6);

    additionalLayout->addWidget(buttonAddSOM = new Button(ButtonStruct("+",QSize(50,25))),4,5,1,1);
    additionalLayout->addWidget(buttonRemoveSOM = new Button(ButtonStruct("-",QSize(50,25))),4,6,1,1);

    connect(buttonAddSOM, SIGNAL(clicked()), controller, SLOT(addSourceOfMember()));
    connect(buttonRemoveSOM, SIGNAL(clicked()), controller, SLOT(removeSourceOfMember()));
}

void ContractorDialogView::settingsChanged(const QString element)
{
    emit settingsChangedSignal(element);
}

QLineEdit *ContractorDialogView::getLineSymbol() {return lineSymbol;}
QLineEdit *ContractorDialogView::getLineName() {return lineName;}
QLineEdit *ContractorDialogView::getTextCompany() {return textCompany;}
QLineEdit *ContractorDialogView::getLinePostCode() {return linePostCode;}
QLineEdit *ContractorDialogView::getLineCity() {return lineCity;}
QLineEdit *ContractorDialogView::getLineAdress() {return lineAdress;}
QLineEdit *ContractorDialogView::getLineTIN() {return lineTIN;}
QLineEdit *ContractorDialogView::getLineRegon() {return lineRegon;}
QLineEdit *ContractorDialogView::getLineAccount() {return lineAccount;}
QLineEdit *ContractorDialogView::getLineWebsite() {return lineWebsite;}
QLineEdit *ContractorDialogView::getLineEmail() {return lineEmail;}
QLineEdit *ContractorDialogView::getLineDiscount() {return lineDiscount;}
QLineEdit *ContractorDialogView::getLineAdditional() {return lineAdditional;}
QTableView *ContractorDialogView::getTablePhones() {return phones;}
QTextEdit *ContractorDialogView::getTextComments() {return textComments;}
QComboBox *ContractorDialogView::getBoxConGroup() {return boxConGroup;}
QComboBox *ContractorDialogView::getBoxSOM() {return boxSOM;}
QComboBox *ContractorDialogView::getBoxAdditionalId(){return boxAdditionalId;}
QRadioButton *ContractorDialogView::getRadioBusiness(){return radioBusiness;}
QRadioButton *ContractorDialogView::getRadioIndividial(){return radioIndividual;}
QCheckBox *ContractorDialogView::getCheckBoxSupplier(){return checkBoxSupplier;}
QCheckBox *ContractorDialogView::getCheckBoxBuyer(){return checkBoxBuyer;}
QLabel *ContractorDialogView::getLabelName() {return labelName;}
QLabel *ContractorDialogView::getLabelCompany(){return labelCompany;}
QLabel *ContractorDialogView::getLabelTIN(){return labelTIN; }
ButtonBox *ContractorDialogView::getButtonBox(){ return this->buttonBox; }

