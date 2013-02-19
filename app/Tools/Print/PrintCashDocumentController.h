#ifndef PRINTCASHDOCUMENTCONTROLLER_H
#define PRINTCASHDOCUMENTCONTROLLER_H


#include "Tools/Print/PrintDialogController.h"

class PrintCashDocumentController : public PrintDialogController
{
    Q_OBJECT

public:
    PrintCashDocumentController(QString symbol);
    void createDirectories();
    void setOutputFile();
    void printRelated(QVector<SimpleDocumentInfo> vectorDoc);

public slots:

    void printPreviewFile();
};

#endif // PRINTCASHDOCUMENTCONTROLLER_H
