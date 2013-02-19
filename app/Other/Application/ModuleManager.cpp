#include "ModuleManager.h"

ModuleManager::ModuleManager(QObject *parent) :
    QObject(parent)
{
}

void ModuleManager::addModule(Module module){

    if (!modules.contains(module))
        modules.push_back(module);
}

bool ModuleManager::contains(Module module){

    return modules.contains(module);
}

