#ifndef PRINTSALEDOCUMENTCONTROLLER_H
#define PRINTSALEDOCUMENTCONTROLLER_H

#include "Tools/Print/PrintDialogController.h"
#include "Tools/Print/PrintSaleDocumentManager.h"

class PrintSaleDocumentController : public PrintDialogController
{
    Q_OBJECT

private:

    PrintSaleDocumentManager* saleManager;

public:
    PrintSaleDocumentController(QString symbol);
    void print(Invoice* document);
    void print(DocumentZAL* document);
    void print(DocumentFK *document);
    void printRelated(QVector<SimpleDocumentInfo> vectorDoc);
    void createDirectories();
    void setOutputFile();

    void setSaleManager(PrintSaleDocumentManager* saleManager);
    PrintSaleDocumentManager* getSaleManager();
public slots:
    void printPreviewFile();
};

#endif // PRINTSALEDOCUMENTCONTROLLER_H
