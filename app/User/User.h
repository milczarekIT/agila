#ifndef USER_H
#define USER_H

#include <QString>


class User
{
    QString login;
    QString name;
    int type;   // admin | użytkownik - admin może dodawać, kasować użytkowników
public:
    User();
    User(QString login, QString name, int type);
    ~User();

    static const int TYPE_USER = 0;
    static const int TYPE_ADMIN = 1;

    void setLogin(QString login);
    void setName(QString name);
    void setType(int type);
    int operator ==(User u);

    QString getLogin();
    QString getName();
    int getType();

    bool isAdmin();
};

#endif // USER_H
