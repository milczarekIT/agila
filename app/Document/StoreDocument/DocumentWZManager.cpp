#include "DocumentWZManager.h"

DocumentWZManager::DocumentWZManager()
{
    this->documentWZPolicy = new DocumentWZPolicy();
}

DocumentWZManager::~DocumentWZManager(){}

void DocumentWZManager::setContractor(Contractor c)
{
 this->documentWZPolicy->setContractor(c);
}

Contractor DocumentWZManager::getContractor()
{
    return this->documentWZPolicy->getContractor();
}
