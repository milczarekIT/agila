#include "User.h"

User::User()
{
}

User::User(QString login, QString name, int type)
{
    this->login = login;
    this->name = name;
    this->type = type;
}

User::~User()
{
}

void User::setLogin(QString login) {
    this->login = login;
}

void User::setName(QString name) {
    this->name = name;
}

void User::setType(int type) {
    this->type = type;
}

QString User::getLogin() {
    return login;
}

QString User::getName(){
    return name;
}

int User::getType() {
    return type;
}

bool User::isAdmin() {
    return (type == User::TYPE_ADMIN);
}

int User::operator ==(User u)
{
    if(this->login != u.getLogin())
        return 0;
    else if(this->name != u.getName())
        return 0;
    else
        return 1;
}
