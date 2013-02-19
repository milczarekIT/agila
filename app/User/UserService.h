#ifndef USERSERVICE_H
#define USERSERVICE_H

#include "User/User.h"
#include "User/UserModel.h"

class UserService
{
    UserModel *model;
public:
    UserService();
    ~UserService();

    bool isCorrectLogin(QString login, QString password);
    bool isLoginInDatabase(QString login);

    QVector<User> getUsers();
    User getUser(QString login);
    void addUser(User user, QString password);
    QString getPassword(QString login);

};

#endif // USERSERVICE_H
