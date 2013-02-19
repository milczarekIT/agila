#include "DocumentPAManager.h"

DocumentPAManager::DocumentPAManager()
{
    this->invoicePolicy= new DocumentPAPolicy();
}

DocumentPAManager::~DocumentPAManager()
{
    delete invoicePolicy;
}


