#include "SaleManager.h"

SaleManager::SaleManager(){}

SaleManager::~SaleManager(){}


Contractor SaleManager::getContractor()
{
return this->getInvoicePolicy()->getContractor();
}
void SaleManager::setContractor(Contractor c)
{
this->getInvoicePolicy()->setContractor(c);
}
