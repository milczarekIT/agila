#include "DocumentPZManager.h"

DocumentPZManager::DocumentPZManager()
{
    this->documentPZPolicy= new DocumentPZPolicy();
}

DocumentPZManager::~DocumentPZManager(){}

void DocumentPZManager::setContractor(Contractor c)
{
 this->documentPZPolicy->setContractor(c);
}

Contractor DocumentPZManager::getContractor()
{
    return this->documentPZPolicy->getContractor();
}
