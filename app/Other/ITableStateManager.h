#ifndef ITABLESTATEMANAGER_H
#define ITABLESTATEMANAGER_H

#include "Other/TableStateManager.h"

/**
  * @author Bartosz Milczarek
  * Klasa interfejsowa wymuszająca zapis i odczyt ustawień/stanu tabeli (nagłówka - kolumn)
  */
class ITableStateManager
{
protected:
    TableStateManager *tableStateManager;

    virtual void restoreTableState() = 0;
    virtual void saveTableState() = 0;
public:
    ITableStateManager();
};

#endif // ITABLESTATEMANAGER_H
