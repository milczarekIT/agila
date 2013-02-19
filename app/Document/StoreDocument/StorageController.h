#ifndef StorageController_H
#define StorageController_H

#include "Document/StoreDocument/StoreDocumentController.h"
#include "Document/StoreDocument/StorageService.h"
#include "Document/StoreDocument/StorageView.h"
#include "Document/StoreDocument/StorageManager.h"
#include "Tools/Print/PrintStoreDocumentController.h"

class DocumentPZView;

class StorageController : public StoreDocumentController  {
    Q_OBJECT

public:
    StorageController(QWidget* parent,bool edit,QString symbol);
    ~StorageController();
    void exec();
    void exec(QString symbol);

private:
    StorageService *stService;
    void fillBox(QComboBox *box,QVector<SimpleStructure> values);
    bool isChangesOccured();
    void restoreTableState();
    void saveTableState();

public slots:
    void printDoc();
    void getDocumentData();

};

#endif // StorageController_H
