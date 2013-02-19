#ifndef PRINTPURCHASEDOCUMENTMANAGER_H
#define PRINTPURCHASEDOCUMENTMANAGER_H

#include "Tools/Print/PrintManager.h"

class PrintPurchaseDocumentManager : public PrintManager
{
public:
    PrintPurchaseDocumentManager();
    void print(DocumentNK *document,QString copyOrOriginal, QPrinter *drukarka);
    void print(DocumentFZK *document,QString copyOrOriginal, QPrinter *drukarka);
    void prepareToPrint(QString name,PurchaseInvoice *document,QString copyOrOriginal,QPrinter* drukarka);
    void print(PurchaseInvoice *document,QString copyOrOriginal,QPrinter* drukarka);
    void printPurchaseDocument(PurchaseInvoice *document,QString copyOrOriginal,QPrinter *drukarka);
};

#endif // PRINTPURCHASEDOCUMENTMANAGER_H
