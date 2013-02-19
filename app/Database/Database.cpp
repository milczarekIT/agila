#include "Database.h"

Database::Database()
{
    db = QSqlDatabase::addDatabase("QPSQL","AgilaDatabase");
    initConnection();
}

Database::~Database()
{
    if(db.isOpen()) db.close();
}

void Database::initConnection()
{
    settings.beginGroup("Database");
    db.setHostName("localhost");
    db.setDatabaseName(settings.value("database").toString());
    db.setUserName(settings.value("username").toString());
    db.setPassword(settings.value("password").toString());
    db.setPort(settings.value("port").toInt());
    settings.endGroup();

    db.open();
}


Database& Database::getInstance()
{
    static Database instance;
    return instance;
}
