#ifndef PRINTORDERDOCUMENTMANAGER_H
#define PRINTORDERDOCUMENTMANAGER_H

#include "Tools/Print/PrintManager.h"
#include "Document/OrderDocument/Order.h"

class PrintOrderDocumentManager : public PrintManager
{
public:
    PrintOrderDocumentManager();

    void print(Order *document,QString copyOrOriginal, QPrinter *drukarka);
};

#endif // PRINTORDERDOCUMENTMANAGER_H
