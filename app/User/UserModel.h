#ifndef USERMODEL_H
#define USERMODEL_H

#include "Database/Model.h"
#include "User/User.h"

class UserModel : public Model
{
public:
    UserModel();
    ~UserModel();

    // hash - zakodowane hasło
    bool isCorrectLogin(QString login, QString hash);
    bool isLoginInDatabase(QString login);

    QVector<User> getUsers();
    User *getUser(QString login);
    void addUser(User user, QString hash);
    QString getPassword(QString login);
    void editUser(User *u, QString oldLogin);
    void editPassword(User *u, QString password);
    void removeUser(QString login);
};

#endif // USERMODEL_H
