#include "UserModel.h"

UserModel::UserModel()
{
}

UserModel::~UserModel() {

}

bool UserModel::isCorrectLogin(QString login, QString hash)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT id FROM users WHERE login = ? AND password = ? AND is_active = true");
    query->addBindValue(login);
    query->addBindValue(hash);
    query->exec();

    int size = query->size();

    delete query;

    return (size > 0) ? true : false;
}

bool UserModel::isLoginInDatabase(QString login)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT id FROM users WHERE login = ? AND is_active = true");
    query->addBindValue(login);
    query->exec();

    if(query->lastError().isValid())
        throw new SQLException("UserModel::isLoginInDatabase", query);

    int size = query->size();

    delete query;

    return (size > 0) ? true : false;
}

QVector<User> UserModel::getUsers() {
    QVector<User> users;

    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT login, name, type FROM users WHERE is_active = true");
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("UserModel::getUsers()", query);
    else
    {
        User *user = new User();
        while(query->next())
        {
            user->setLogin(query->value(0).toString());
            user->setName(query->value(1).toString());
            user->setType(query->value(2).toInt());
            users.push_back(*user);
        }
        delete user;
        delete query;
    }

    return users;
}

User UserModel::getUser(QString login) {
    User user;

    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT login, name, type FROM users "
                          "WHERE login = ? AND is_active = true");
    query->addBindValue(login);
    query->exec();

    if(query->lastError().isValid())
        throw new SQLException("UserModel::getUser", query);

    if(query->size() > 0) {
        query->first();
        user.setLogin(query->value(0).toString());
        user.setName(query->value(1).toString());
        user.setType(query->value(2).toInt());
    }
    delete query;

    return user;
}

void UserModel::addUser(User user, QString hash) {

    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("INSERT INTO users (id, login, password, name, type,is_active) "
                   "VALUES (DEFAULT,?,?,?,?,?)");
    query->addBindValue(user.getLogin());
    query->addBindValue(hash);
    query->addBindValue(user.getName());
    query->addBindValue(user.getType());
    query->addBindValue(true);
    query->exec();

    if(query->lastError().isValid())
        throw new SQLException("UserModel::isLoginInDatabase", query);

    delete query;

}

QString UserModel::getPassword(QString login) {
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT password FROM users WHERE login = ? AND is_active = true");
    query->addBindValue(login);
    query->exec();

    if(query->lastError().isValid())
        throw new SQLException("UserModel::isLoginInDatabase", query);

    QString hash;
    if(query->size() > 0) {
        query->first();
        hash = query->value(0).toString();
    }

    delete query;

    return hash;
}

void UserModel::editUser(User u, QString oldLogin)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE users SET login = :newlogin, name = :name WHERE login = :oldlogin");
    query->bindValue(":newlogin",u.getLogin());
    query->bindValue(":name",u.getName());
    query->bindValue(":oldlogin",oldLogin);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("UserModel::editUser", query);

    delete query;
}

void UserModel::editPassword(User u, QString password)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE users SET password = :pass WHERE login = :login");
    query->bindValue(":pass",password);
    query->bindValue(":login",u.getLogin());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("UserModel::editUser", query);

    delete query;
}

void UserModel::removeUser(QString login)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE users SET is_active = true WHERE login = :login");
    query->bindValue(":login",login);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("UserModel::removeUser", query);
    delete query;
}
