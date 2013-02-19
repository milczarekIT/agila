#include "InvoiceManager.h"

InvoiceManager::InvoiceManager()
{
    this->invoicePolicy= new InvoicePolicy();
}

InvoiceManager::~InvoiceManager()
{
    delete invoicePolicy;
}

