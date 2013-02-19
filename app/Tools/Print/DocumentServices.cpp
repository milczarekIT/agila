#include "DocumentServices.h"

DocumentServices::DocumentServices()
{
}

Invoice DocumentServices::getInvoice(QString symbol)
{
    invService = new InvoiceService();
    Invoice inv;
    inv = invService->getInvoice(symbol);
    delete invService;
    return inv;
}
DocumentFK DocumentServices::getFK(QString symbol)
{
    fkService = new DocumentFKService();
    DocumentFK fk;
    fk = fkService->getDocumentFK(symbol);
    delete fkService;
    return fk;
}


PurchaseInvoice DocumentServices::getPurchaseInvoice(QString symbol)
{
    purService = new PurchaseInvoiceService();
    PurchaseInvoice pur;
    pur = purService->getPurchaseInvoice(symbol);
    delete purService;
    return pur;
}
DocumentNK DocumentServices::getNK(QString symbol)
{
    nkService = new DocumentNKService();
    DocumentNK nk;
    nk = nkService->getDocumentNK(symbol);
    delete nkService;
    return nk;
}

DocumentFZK DocumentServices::getFZK(QString symbol)
{
    fzkService = new DocumentFZKService();
    DocumentFZK fzk;
    fzk = fzkService->getDocumentFZK(symbol);
    delete fzkService;
    return fzk;
}

DocumentZAL DocumentServices:: getZAL(QString symbol)
{
    zalService = new DocumentZALService();
    DocumentZAL zal;
    zal = zalService->getDocumentZAL(symbol);
    delete zalService;
    return zal;
}
DocumentPZ DocumentServices::getPZ(QString symbol)
{
    pzService = new DocumentPZService();
    DocumentPZ pz;
    pz = pzService->getDocumentPZ(symbol);
    delete pzService;
    return pz;
}
DocumentWZ DocumentServices::getWZ(QString symbol)
{
    wzService = new DocumentWZService();
    DocumentWZ wz;
    wz = wzService->getDocumentWZ(symbol);
    delete wzService;
    return wz;
}
StoreDocument DocumentServices::getStore(QString symbol)
{
    stService = new StorageService();
    StoreDocument st;
    st = stService->getStoreDocument(symbol);
    delete stService;
    return st;
}

Order DocumentServices::getOrder(QString symbol)
{
    orService = new OrderService();
    Order order;
    order = orService->getOrder(symbol);
    delete orService;
    return order;
}
