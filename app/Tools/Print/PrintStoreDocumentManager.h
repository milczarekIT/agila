#ifndef PRINTSTOREDOCUMENTMANAGER_H
#define PRINTSTOREDOCUMENTMANAGER_H

#include "Tools/Print/PrintManager.h"

class PrintStoreDocumentManager : public PrintManager
{
public:
    PrintStoreDocumentManager();
    void print(StoreDocument*document,QString copyOrOriginal, QPrinter *drukarka);
    void print(DocumentPZ *document,QString copyOrOriginal ,QPrinter *drukarka);
    void print(DocumentWZ *document,QString copyOrOriginal, QPrinter *drukarka);

private:
    void printStoreDocument(StoreDocument*document,QString copyOrOriginal,QPrinter* drukarka);
    void prepareToPrint(QString name,StoreDocument *document,QString copyOrOriginal,QPrinter* drukarka);
    void setRoles(QString name);
};

#endif // PRINTSTOREDOCUMENTMANAGER_H
