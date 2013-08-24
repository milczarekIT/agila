#include "ApplicationManager.h"

ApplicationManager* ApplicationManager::instance = 0;

ApplicationManager::ApplicationManager()
{
    loggedUser = 0;
    WarehouseService *service = new WarehouseService();
    this->currentWarehouse = service->getDefaultWarehouse();
    delete service;

    this->applicationMode = ApplicationManager::AGILA_FAKTURY;
    modulesManager = new ModuleManager();

    initApplicationConfig();
}

const QString ApplicationManager::APP_DATA_DIR = QDir::homePath() + QDir::separator() + ".agila";
const QString ApplicationManager::DIR_HOME_AGILA = QDir::homePath() + QDir::separator() + "agila";

ApplicationManager::~ApplicationManager(){}

ApplicationManager* ApplicationManager::getInstance()
{
    if(!instance) {
        instance = new ApplicationManager();
    }
    return instance;
}

void ApplicationManager::initApplicationConfig()
{
    modulesManager = new ModuleManager();

    if(isAgilaFaktury())
    {
        applicationName = "Agila Faktury";

        modulesManager->addModule(ModuleManager::Goods);
        modulesManager->addModule(ModuleManager::Contractors);
        modulesManager->addModule(ModuleManager::Sale);
    }
    else if(isAgilaS3())
    {
        applicationName = "Agila S3";

        modulesManager->addModule(ModuleManager::Goods);
        modulesManager->addModule(ModuleManager::Contractors);
        modulesManager->addModule(ModuleManager::Sale);
        modulesManager->addModule(ModuleManager::Purchase);
        modulesManager->addModule(ModuleManager::Cash);
        modulesManager->addModule(ModuleManager::Order);
        modulesManager->addModule(ModuleManager::Warehouses);
        modulesManager->addModule(ModuleManager::Reports);
        modulesManager->addModule(ModuleManager::Price);
    }

}

User* ApplicationManager::getLoggedUser()
{
    return loggedUser;
}

Warehouse *ApplicationManager::getWarehouse()
{
    return currentWarehouse;
}

QString ApplicationManager::getApplicationName() {
    return this->applicationName;
}

int ApplicationManager::getWarehouseId() {
    return currentWarehouse->getId();
}

void ApplicationManager::setLoggedUser(User* user)
{
    this->loggedUser = user;
}

void ApplicationManager::setWarehouse(Warehouse warehouse)
{
    *currentWarehouse = warehouse;
}

bool ApplicationManager::isAgilaFaktury() {
    return (applicationMode == ApplicationManager::AGILA_FAKTURY);
}

bool ApplicationManager::isAgilaS3() {
    return (applicationMode == ApplicationManager::AGILA_S3);
}

bool ApplicationManager::containsModule(ModuleManager::Module module)
{
    return modulesManager->contains(module);
}
