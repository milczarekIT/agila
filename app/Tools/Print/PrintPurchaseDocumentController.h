#ifndef PRINTPURCHASEDOCUMENTCONTROLLER_H
#define PRINTPURCHASEDOCUMENTCONTROLLER_H

#include "Tools/Print/PrintDialogController.h"
#include "Tools/Print/PrintPurchaseDocumentManager.h"

class PrintPurchaseDocumentController : public PrintDialogController
{
    Q_OBJECT

public:
    PrintPurchaseDocumentManager* purchaseManager;
    PrintPurchaseDocumentController(QString symbol);
    void print(DocumentNK *document);
    void print(DocumentFZK *document);
    void print(PurchaseInvoice* document);
    void createDirectories();
    void setOutputFile();
    void printRelated(QVector<SimpleDocumentInfo> vectorDoc);

    void setPurchaseManager(PrintPurchaseDocumentManager* purchaseManager);
    PrintPurchaseDocumentManager* getPurchaseManager();
public slots:

    void printPreviewFile();
};

#endif // PRINTPURCHASEDOCUMENTCONTROLLER_H
