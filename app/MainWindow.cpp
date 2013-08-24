#include "MainWindow.h"
#include <QDockWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    initStartConf();
}

MainWindow::~MainWindow() {
}

void MainWindow::initStartConf() {
    this->setCentralWidget(window = new QWidget());
    window->setLayout(mainLayout = new QGridLayout());
    this->setMinimumHeight(768);
    this->setMinimumWidth(1024);
    this->setWindowState(Qt::WindowMaximized);
    this->setStatusBar(statusBar = new QStatusBar());
    idleTimer = new QTimer(this);
    idleTimer->setInterval(800000000);
    initMainInterface();
    initConnections();
    setTabOrders();
    setMainWindowUserInfo();
}

void MainWindow::initMainInterface() {
    menu = new MainMenuController();
    mainLayout->addWidget(menu->getView(),1,0);
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
    {
        storeComboBox = new MainStoreComboBoxController();
        mainLayout->addWidget(storeComboBox->getView(),1,1);
    }
    mainLayout->addItem(new QSpacerItem(20,0, QSizePolicy::Expanding, QSizePolicy::Minimum),1,2);
    mainLayout->addWidget(tab = new MainTab(this),2,0,1,5);
    mainLayout->addWidget(centralElement = new QStackedWidget,3,0,1,5);
    mainLayout->addItem(verticalSpacer = new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Minimum),5,0,1,5);
    addTableViewsAsCentralElements();
    mainLayout->addWidget(loggedUser = new QLabel(),1,3);

    if(ApplicationManager::getInstance()->getLoggedUser() != NULL) {
        buttonLogout = new Button(ButtonStruct("Wyloguj", "Wyloguj aktualnego użytkownika", QSize(120,25)));
        mainLayout->addWidget(buttonLogout,1,4);
    }
}

void MainWindow::addTableViewsAsCentralElements() {
    for(int index = 0; index < tab->getMainTabItemControllersVector().size(); index++)
    {
        if(tab->getMainTabItemControllersVector()[index]->getView()->getTableView() != NULL)
            centralElement->addWidget(tab->getMainTabItemControllersVector()[index]->getView()->getTableView());
    }
}

void MainWindow::setCurrentTab(int index) {
    if(index < tab->getMainTabItemControllersVector().size())
    {
        ModuleManager::Module currentModule = tab->getMainTabItemControllersVector()[index]->module();

        if(this->isModuleWithTableView(currentModule))
        {
            centralElement->show();
            centralElement->setCurrentIndex(index);
            tab->getMainTabItemControllersVector()[index]->refreshTable();
            verticalSpacer->changeSize(0,0, QSizePolicy::Expanding, QSizePolicy::Minimum);
            tab->setMaximumHeight(170);
        }
    }
    else
    {
        centralElement->hide();
        verticalSpacer->changeSize(0,200,QSizePolicy::Maximum, QSizePolicy::Expanding);
        tab->setMaximumHeight(700);
    }
}

void MainWindow::initConnections() {
    connect(tab, SIGNAL(currentChanged(int)),this, SLOT(setCurrentTab(int)));

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Cash) &&  ApplicationManager::getInstance()->containsModule(ModuleManager::Sale))
        connect(tab->getSale(),SIGNAL(issuedCashDoc()),tab->getCash(),SLOT(initModel()));

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Order) &&  ApplicationManager::getInstance()->containsModule(ModuleManager::Sale))
        connect(tab->getOrder(),SIGNAL(issuedInvoice()),tab->getSale(),SLOT(initModel()));

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Order) &&  ApplicationManager::getInstance()->containsModule(ModuleManager::Purchase))
        connect(tab->getOrder(),SIGNAL(issuedPurchaseInvoice()),tab->getPurchase(),SLOT(initModel()));

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Cash))
        connect(tab->getPurchase(),SIGNAL(issuedDocKW()),tab->getCash(),SLOT(initModel()));

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
    {
        connect(tab->getSettings()->getView()->getTabMagazine(),SIGNAL(warehouseChanged()),storeComboBox,SLOT(setCurrentStoreInStoreComboBox()));
        connect(tab->getSettings()->getView()->getTabMagazine()->getView(),SIGNAL(numberOfMagazinesChanged()),storeComboBox,SLOT(setDataIntoStoreComboBox()));
        connect(storeComboBox,SIGNAL(storeSwitched()),this,SLOT(refreshView()));
    }
    if(ApplicationManager::getInstance()->getLoggedUser() != NULL)
        connect(buttonLogout,SIGNAL(clicked()),this,SLOT(emitLogout()));
    connect(idleTimer,SIGNAL(timeout()),this,SLOT(emitLogout()));
}

void MainWindow::refreshView() {
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Contractors))
        tab->getContractors()->refreshTable();

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Goods))
        tab->getGoods()->refreshTable();

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Order))
        tab->getOrder()->refreshTable();

    //if(ApplicationManager::getInstance()->containsModule(ModuleManager::Cash))
        //tab->getCashDocuments()->refreshTable(); // odkomentować po demie <--  cos nie trybi

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Purchase))
        tab->getPurchase()->refreshTable();

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Sale))
        tab->getSale()->refreshTable();

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
        tab->getStore()->refreshTable();

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Reports))
        tab->getReports()->initModel();

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Settings))
        tab->getSettings()->getSettingsModel();
}

bool MainWindow::isModuleWithTableView(ModuleManager::Module module) {
    QVector<ModuleManager::Module> *modulesWithTableView = new QVector<ModuleManager::Module>();
    modulesWithTableView->push_back(ModuleManager::Goods);
    modulesWithTableView->push_back(ModuleManager::Contractors);
    modulesWithTableView->push_back(ModuleManager::Sale);
    modulesWithTableView->push_back(ModuleManager::Purchase);
    modulesWithTableView->push_back(ModuleManager::Order);
    modulesWithTableView->push_back(ModuleManager::Cash);
    modulesWithTableView->push_back(ModuleManager::Warehouses);
    modulesWithTableView->push_back(ModuleManager::Price);

    bool contains = modulesWithTableView->contains(module);
    delete modulesWithTableView;

    return contains;
}

void MainWindow::show() {
    QMainWindow::show();
    initAutoRemovingOldBackups();
    checkApplicationUpdates();
}

void MainWindow::setTabOrders() {
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
        setTabOrder(storeComboBox,tab);

    if(ApplicationManager::getInstance()->getLoggedUser() != NULL)
        setTabOrder(tab,buttonLogout);
}

void MainWindow::initAutoRemovingOldBackups() {
    ArchiverAutoRemover *autoRemover = new ArchiverAutoRemover();
    autoRemover->checkAndRemoveOldBackups();
    delete autoRemover;
}

void MainWindow::checkApplicationUpdates() {
    UpdateHelper *updateHelper = new UpdateHelper();
    updateHelper->checkApplicationUpdates();
    delete updateHelper;
}

void MainWindow::setMainWindowUserInfo() {
    QString text = Style::getInstance()->getLogginUserInfo();
    if(ApplicationManager::getInstance()->getLoggedUser() != NULL)
        loggedUser->setText(text + "<b>"+ ApplicationManager::getInstance()->getLoggedUser()->getName() + "</b></font>    " );
    else
        loggedUser->setText("");
}

void MainWindow::closeEvent(QCloseEvent *event){
    ArchiverReminder *reminder = new ArchiverReminder();
    reminder->checkPreferencesAndRemind();
    delete reminder;

    event->accept();
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    event->type();
    timerStart();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    event->type();
    timerStart();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    event->type();
    timerStart();
}

void MainWindow::timerStart() {
    idleTimer->start();
}

void MainWindow::timerStop() {
    idleTimer->stop();
}

void MainWindow::emitLogout() {
    emit logout();
}

MainTab *MainWindow::getTab() {
    return tab;
}

QTimer *MainWindow::getIdleTimer() {
    return idleTimer;
}
