#include "StorageManager.h"

StorageManager::StorageManager()
{
    this->storagePolicy= new StoragePolicy();
}

StorageManager::~StorageManager(){}

void StorageManager::setContractor(Contractor c)
{
 this->storagePolicy->setContractor(c);
}

Contractor StorageManager::getContractor()
{
    return this->storagePolicy->getContractor();
}
