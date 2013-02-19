#ifndef PRINTSALEDOCUMENTMANAGER_H
#define PRINTSALEDOCUMENTMANAGER_H

#include "Tools/Print/PrintManager.h"

class PrintSaleDocumentManager : public PrintManager
{
public:
    PrintSaleDocumentManager();
    void print(Invoice *document,QString copyOrOriginal, QPrinter *drukarka);
    void print(DocumentZAL *document,QString copyOrOriginal, QPrinter *drukarka);
    void print (DocumentFK *document,QString copyOrOriginal, QPrinter *drukarka);

private:
    void printSaleDocument(Invoice *document,QString copyOrOriginal, QPrinter* drukarka);
    void printZAL(DocumentZAL *document,QString copyOrOriginal,QPrinter* drukarka);
    void prepareToPrint(QString name,Invoice *document,QString copyOrOriginal, QPrinter* drukarka);
    double countToPay(QVector<DocumentPosition> documentPosition,QVector<SimpleDocumentInfo> previous,double discount);
};

#endif // PRINTSALEDOCUMENTMANAGER_H
