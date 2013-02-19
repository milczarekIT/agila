#include "TableStateManager.h"

TableStateManager::TableStateManager()
{
    settings = new QSettings();
    settings->beginGroup("TableStates");
}

TableStateManager::~TableStateManager() {
    settings->endGroup();
    delete settings;
}

void TableStateManager::saveState(QString tableName, QByteArray state) {
    settings->setValue(tableName, state);
}

QByteArray TableStateManager::getState(QString tableName) {
    return  settings->value(tableName).toByteArray();
}
