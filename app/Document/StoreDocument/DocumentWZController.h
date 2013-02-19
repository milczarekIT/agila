#ifndef DocumentWZController_H
#define DocumentWZController_H

/**
  @author Daniel Wojda

  */

#include "Document/StoreDocument/StoreDocumentController.h"
#include "Document/StoreDocument/DocumentWZService.h"
#include "Document/StoreDocument/DocumentWZView.h"
#include "Document/StoreDocument/DocumentWZManager.h"
#include "Tools/Print/PrintStoreDocumentController.h"


class DocumentWZView;

class DocumentWZController : public StoreDocumentController  {

    Q_OBJECT

public:
    DocumentWZController(QWidget* parent,bool edit);
    ~DocumentWZController();
    void exec();
    void exec(QString symbol);

private:
    DocumentWZService *wzService;
    TransportModel *transportModel;
    void fillBox(QComboBox *box,QVector<SimpleStructure> values);
    bool isChangesOccured();
    void insertInvoiceData(Document invoice);
    void restoreTableState();
    void saveTableState();

public slots:
    void printDoc();
    void getDocumentData();
    void selectOrderOrFacture();
};

#endif // DocumentWZController_H
