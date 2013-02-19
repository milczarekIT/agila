#ifndef PRINTORDERDOCUMENTCONTROLLER_H
#define PRINTORDERDOCUMENTCONTROLLER_H


#include "Tools/Print/PrintDialogController.h"
#include "Tools/Print/PrintOrderDocumentManager.h"

class PrintOrderDocumentController : public PrintDialogController
{
    Q_OBJECT

public:
    PrintOrderDocumentManager* orderManager;
    PrintOrderDocumentController(QString symbol);
    void print(Order *document);
    void createDirectories();
    void setOutputFile();
    void printRelated(QVector<SimpleDocumentInfo> vectorDoc);

    void setOrderManager(PrintOrderDocumentManager* orderManager);
    PrintOrderDocumentManager* getOrderManager();
public slots:

    void printPreviewFile();
};

#endif // PRINTORDERDOCUMENTCONTROLLER_H
