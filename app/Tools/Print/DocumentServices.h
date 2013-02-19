#ifndef DOCUMENTSERVICES_H
#define DOCUMENTSERVICES_H

#include "Document/SaleDocument/DocumentFKService.h"
#include "Document/SaleDocument/InvoiceService.h"
#include "Document/SaleDocument/DocumentZALService.h"
#include "Document/StoreDocument/DocumentPZService.h"
#include "Document/StoreDocument/DocumentWZService.h"
#include "Document/StoreDocument/StorageService.h"
#include "Document/PurchaseDocument/DocumentFZKService.h"
#include "Document/PurchaseDocument/PurchaseInvoiceService.h"
#include "Document/PurchaseDocument/DocumentNKService.h"
#include "Document/OrderDocument/OrderService.h"

class DocumentServices
{
public:

    DocumentServices();
    Invoice getInvoice(QString symbol);
    DocumentFK getFK(QString symbol);
    DocumentFZK getFZK(QString symbol);
    DocumentZAL getZAL(QString symbol);
    DocumentPZ getPZ(QString symbol);
    DocumentWZ getWZ(QString symbol);
    PurchaseInvoice getPurchaseInvoice(QString symbol);
    DocumentNK getNK(QString symbol);
    StoreDocument getStore(QString symbol);
    Order getOrder(QString symbol);
private:
    DocumentFKService *fkService;
    DocumentFZKService *fzkService;
    InvoiceService *invService;
    DocumentZALService* zalService;
    DocumentPZService* pzService;
    DocumentWZService* wzService;
    StorageService* stService;
    OrderService *orService;
    PurchaseInvoiceService* purService;
    DocumentNKService* nkService;

};

#endif // DOCUMENTSERVICES_H
