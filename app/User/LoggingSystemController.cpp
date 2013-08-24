#include "LoggingSystemController.h"

LoggingSystemController::LoggingSystemController()
{
    view = new LoggingSystemView(this);
    service = new UserService();
}

LoggingSystemView *LoggingSystemController::getView()
{
    return view;
}

LoggingSystemController::~LoggingSystemController()
{
    delete view;
    delete service;
}

bool LoggingSystemController::exec()
{
    int signalFromView;
    QString login;
    QString password;

    while(true)
    {
        signalFromView = view->exec();
        login = view->getLogin();
        password = view->getPassword();

        if(signalFromView == QDialog::Accepted)
        {
            if(checkLogin(login))
            {
                if(checkPassword(login,password))
                {
                    User *u = service->getUser(login);
                    ApplicationManager::getInstance()->setLoggedUser(u);
                    view->emitLoggingSignal(u);
                    return true;
                }
                else
                    view->showWrongPassword();
            }
            else
                view->showWrongLogin();
        }
        else
            return false;
    }
}

bool LoggingSystemController::checkLogin(QString login)
{
    UserModel model;
    return model.isLoginInDatabase(login);
}

bool LoggingSystemController::checkPassword(QString login, QString password)
{
    QByteArray noHashedPassword = password.toUtf8();
    QByteArray hashedPassword;

    QCryptographicHash* hash = new QCryptographicHash(QCryptographicHash::Md5);
    hash->addData(noHashedPassword);
    hashedPassword = hash->result().toHex();

    delete hash;

    return service->isCorrectLogin(login, hashedPassword);
}

void LoggingSystemController::checkUserAccess()
{
    QString login = view->getLogin();

    if(view->getLogin().isEmpty())
    {
        view->getInfoAboutUserAccess()->setText("");
    }
    else
    {
        User *u = service->getUser(login);
        if(u == NULL || u->getLogin().isEmpty())
        {
            view->getInfoAboutUserAccess()
                    ->setText("<font color=\"brown\">Podany użytkownik nie istnieje <b>!!!</b></font>");
        }
        else
        {
            view->getInfoAboutUserAccess()
                    ->setText("<font color=\"green\">" + u->getName() + "</font>");
        }
    }
}
