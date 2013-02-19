#ifndef TABLESTATEMANAGER_H
#define TABLESTATEMANAGER_H

#include <QString>
#include <QSettings>
#include <QDebug>

class TableStateManager
{
    QSettings *settings;
public:
    TableStateManager();
    ~TableStateManager();

    void saveState(QString tableName, QByteArray state);
    QByteArray getState(QString tableName);
};

#endif // TABLESTATEMANAGER_H
