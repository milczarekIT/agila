#include "PurchaseManager.h"

PurchaseManager::PurchaseManager()
{
    this->purchasePolicy= new PurchasePolicy();
}

Contractor PurchaseManager::getContractor()
{
return this->getPurchasePolicy()->getContractor();
}
void PurchaseManager::setContractor(Contractor c)
{
this->getPurchasePolicy()->setContractor(c);
}

