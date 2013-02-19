#ifndef APPLICATIONMANAGER_H
#define APPLICATIONMANAGER_H

#include <QDebug>
#include "User/User.h"
#include "Other/Warehouse/WarehouseService.h"
#include "Other/Application/ModuleManager.h"
class WarehouseService;

class ApplicationManager
{

private:
    static ApplicationManager* instance;
    ApplicationManager();
    ~ApplicationManager();

    int applicationMode;

    User loggedUser;
    ModuleManager *modulesManager;
    Warehouse *currentWarehouse;
    QString applicationName;

    void initApplicationConfig();

public:
    static ApplicationManager* getInstance();
    User getLoggedUser();
    Warehouse* getWarehouse();
    int getWarehouseId();
    QString getApplicationName();
    bool containsModule(ModuleManager::Module module);

    void setLoggedUser(User user);
    void setWarehouse(Warehouse warehouse);

    bool isAgilaFaktury();
    bool isAgilaS3();

    /* w Logger::PATH jest ręcznie podany katalog - zmienić */
    static const QString APP_DATA_DIR;
    static const QString DIR_HOME_AGILA;

    const static int AGILA_FAKTURY = 2;
    const static int AGILA_S3 = 3;

};

#endif // APPLICATIONMANAGER_H
