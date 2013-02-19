#ifndef PRINTSTOREDOCUMENTCONTROLLER_H
#define PRINTSTOREDOCUMENTCONTROLLER_H


#include "Tools/Print/PrintDialogController.h"
#include "Tools/Print/PrintStoreDocumentManager.h"

class PrintStoreDocumentController : public PrintDialogController
{
    Q_OBJECT

public:
    PrintStoreDocumentManager* storeManager;

    PrintStoreDocumentController(QString symbol);
    void print(DocumentPZ *document);
    void print(DocumentWZ *document);
    void print(StoreDocument *document);
    void createDirectories();
    void setOutputFile();
    void printRelated(QVector<SimpleDocumentInfo> vectorDoc);

    void setStoreManager(PrintStoreDocumentManager* storeManager);
    PrintStoreDocumentManager* getStoreManager();

public slots:

    void printPreviewFile();
};

#endif // PRINTSTOREDOCUMENTCONTROLLER_H
