#ifndef LOGGINGSYSTEMCONTROLLER_H
#define LOGGINGSYSTEMCONTROLLER_H

#include <QWidget>
#include "User/LoggingSystemView.h"
#include "User/UserModel.h"
#include "User/UserService.h"
#include "Other/Application/ApplicationManager.h"
class LoggingSystemView;

class LoggingSystemController : public QWidget
{
    Q_OBJECT

private:
    LoggingSystemView *view;
    UserService *service;

public:
    explicit LoggingSystemController();
    LoggingSystemView *getView();
    ~LoggingSystemController();
    /*
      true - w przypadku zalogowania się któregokolwiek użytkownika
      false - anulowano logowanie
    */
    bool exec();
    bool checkLogin(QString login);
    bool checkPassword(QString login, QString password);

public slots:
    void checkUserAccess();

};

#endif // LOGGINGSYSTEMCONTROLLER_H
