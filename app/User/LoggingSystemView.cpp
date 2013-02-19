#include "LoggingSystemView.h"

LoggingSystemView::LoggingSystemView(LoggingSystemController *controller)
{
    this->controller = controller;
    this->setWindowTitle("Zaloguj się");
    initComponents();
    initConnections();
}

LoggingSystemView::~LoggingSystemView()
{
    delete layout;
    delete layoutLog;
}

void LoggingSystemView::initComponents()
{
    QFrame *frame = new QFrame();
    frame->setFrameShape(QFrame::Box);
    frame->setFrameShadow(QFrame::Raised);
    frame->setLayout(layoutLog = new QGridLayout);

    buttonBox = new QDialogButtonBox(Qt::Horizontal);
    buttonBox->addButton("Anuluj", QDialogButtonBox::RejectRole);
    buttonBox->addButton("Zaloguj", QDialogButtonBox::AcceptRole);
    this->setLayout(layout = new QGridLayout());

    QImage img ("style/img/logo.png");
    logo = new QLabel();
    logo->setPixmap(QPixmap::fromImage(img));
    this->setLayout(layout);

    layoutLog->addWidget(infoAboutUserAccess = new QLabel(),0,3,1,1);
    layoutLog->addWidget(new QLabel("Użytkownik:"),1,1,1,1);
    layoutLog->addWidget(new QLabel("Hasło:"),2,1,1,1);
    layoutLog->addWidget(lineLogin = new QLineEdit(),1,3,1,1);
    layoutLog->addWidget(linePassword = new QLineEdit(),2,3,1,1);
    layoutLog->addWidget(buttonBox,4,1,1,3,Qt::AlignRight);
    layoutLog->setColumnMinimumWidth(0,20);
    layoutLog->setColumnMinimumWidth(2,20);
    layoutLog->setColumnMinimumWidth(3,230);
    layoutLog->setColumnMinimumWidth(4,20);
    layoutLog->setRowMinimumHeight(0,30);
    layoutLog->setRowMinimumHeight(3,30);
    layoutLog->setRowMinimumHeight(5,30);

    layout->addWidget(frame,1,1,1,1);
    //layout->addWidget(logo,1,0,1,1,Qt::AlignCenter);
    //layout->setColumnMinimumWidth(0,300);
    //layout->setRowMinimumHeight(0,50);
    //layout->setRowMinimumHeight(2,50);
    layout->setColumnMinimumWidth(0,20);
    layout->setColumnMinimumWidth(2,20);
    layout->setRowMinimumHeight(0,20);
    layout->setRowMinimumHeight(2,20);

    infoAboutUserAccess->setMinimumWidth(270);
    linePassword->setEchoMode(QLineEdit::Password);
    frame->setProperty("whiteRoundFrame",true);
}

void LoggingSystemView::showWrongPassword()
{
    MessageBox* box = new MessageBox(this);
    box->createWarningBox("Podane hasło jest błędne");
    delete box;
}

void LoggingSystemView::showWrongLogin()
{
    MessageBox* box = new MessageBox(this);
    box->createWarningBox("Użytkownik o podanej nazwie nie istnieje!");
    delete box;
}

QString LoggingSystemView::getLogin()
{
    return lineLogin->text();
}

QString LoggingSystemView::getPassword()
{
    return linePassword->text();
}

QLabel *LoggingSystemView::getInfoAboutUserAccess()
{
    return infoAboutUserAccess;
}

void LoggingSystemView::emitLoggingSignal(User u)
{
    emit logged(u);
}

void LoggingSystemView::initConnections()
{
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(lineLogin, SIGNAL(editingFinished()), controller, SLOT(checkUserAccess()));
}
