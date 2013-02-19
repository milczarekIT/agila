#ifndef DOCUMENTPZCONTROLLER_H
#define DOCUMENTPZCONTROLLER_H

/**
  @author Daniel Wojda

  */
#include "Document/StoreDocument/StoreDocumentController.h"
#include "Document/StoreDocument/DocumentPZService.h"
#include "Document/StoreDocument/DocumentPZView.h"
#include "Document/StoreDocument/DocumentPZManager.h"
#include "Tools/Print/PrintStoreDocumentController.h"

class DocumentPZView;

class DocumentPZController : public StoreDocumentController  {

    Q_OBJECT

public:
    DocumentPZController(QWidget* parent,bool edit);
    ~DocumentPZController();
    void exec();
    void exec(QString symbol);

private:
    DocumentPZService *pzService;
    TransportModel *transportModel;
    void fillBox(QComboBox *box,QVector<SimpleStructure> values);
    bool isChangesOccured();
    void restoreTableState();
    void saveTableState();


public slots:
    void printDoc();
    void getDocumentData();

};

#endif // DOCUMENTPZCONTROLLER_H
