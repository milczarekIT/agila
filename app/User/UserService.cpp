#include "UserService.h"

UserService::UserService()
{
    model = new UserModel();
}

UserService::~UserService() {
    delete model;
}

bool UserService::isCorrectLogin(QString login, QString password) {
    bool correctLogin = false;
    try {
        correctLogin = model->isCorrectLogin(login, password);
    } catch(SQLException *e) {
        qDebug() << e->getMessage(); // TODO obsługa wyjątku
    }

    return correctLogin;
}

bool UserService::isLoginInDatabase(QString login) {
    bool loginInDatabase = false;
    try {
        loginInDatabase = model->isLoginInDatabase(login);
    } catch(SQLException *e) {
         qDebug() << e->getMessage(); // TODO obsługa wyjątku
    }

    return loginInDatabase;
}

QVector<User> UserService::getUsers() {
    QVector<User> users;
    try {
        users = model->getUsers();
    } catch(SQLException *e) {
        qDebug() << e->getMessage(); // TODO obsługa wyjątku
    }

    return users;
}

User *UserService::getUser(QString login) {
    User *user = NULL;
    try {
        user = model->getUser(login);
    } catch(SQLException *e) {
        qDebug() << e->getMessage(); // TODO obsługa wyjątku
    }

    return user;
}

void UserService::addUser(User user, QString password) {
    try {
        model->addUser(user, password);
    } catch(SQLException *e) {
         qDebug() << e->getMessage(); // TODO obsługa wyjątku
    }
}

QString UserService::getPassword(QString login) {
    QString password;
    try {
        password = model->getPassword(login);
    } catch(SQLException *e) {
        qDebug() << e->getMessage(); // TODO obsługa wyjątku
   }

   return password;
}
