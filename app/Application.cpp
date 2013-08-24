#include "Application.h"

Application::Application(int argc, char *argv[]) : QApplication(argc,argv) {
    initApplication(argc,argv);
}

Application::~Application() {
    delete mainWindow;
    delete logger;
    delete owner;
}

int Application::initApplication(int argc, char *argv[]) {

    if(argc > 1) {
        ArgumentsAnalyzer analyzer;
        analyzer.analyze(argc, argv);
    } else {

        ApplicationInfo appInfo;
        appInfo.initAppliactionPath(argv[0]);
        setAppInformation();
        Style::getInstance()->setApplicationStyle(this);
        return this->run();
    }
}

int Application::run() {
    try {
        login();
        return this->exec();

    } catch(SQLException *e) {
        qDebug() << "Nieprzechwycony wyjątek w metodzie: " << e->getSourceMethod() << "\nKomunikat: " << e->getMessage();
    }
}

void Application::setAppInformation() {
    QCoreApplication::setOrganizationName("Blue Braces");
    QCoreApplication::setOrganizationDomain("bluebraces.com");
    QCoreApplication::setApplicationName("Agila");
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
}

void Application::login() {
    int signal = initLoginWindow();

    if(signal == QDialog::Accepted) {

        ProgressBarDialog::getInstance().showProgresBar("Ładowanie ustawień",0,3000);
        initMainWindow();
        showMainWindow();
        checkOwner();
    }
}

void Application::logout() {
    delete mainWindow;
    login();
}

void Application::initMainWindow() {
    mainWindow = new MainWindow();
    mainWindow->setWindowIcon(QIcon(":/image-theme/logo.png"));
    mainWindow->setIconSize(QSize(48, 48));
    mainWindow->setWindowTitle(ApplicationManager::getInstance()->getApplicationName());
    connect(mainWindow, SIGNAL(logout()), this, SLOT(logout()));
}

void Application::showMainWindow() {
    mainWindow->show();
}

int Application::initLoginWindow() {
    logger = new LoggingSystemController();
    return logger->exec();
}

void Application::checkOwner() {
    owner = new OwnerService();
    if(!owner->isOwnerDefinied()) {
        MessageBox msg;
        msg.createInfoBox("Przejdź do panelu ustawień aby wprowadzić \ndane podmiotu");
    }
    delete owner;
}
