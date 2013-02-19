#ifndef MAINTABSTOREITEMCONTROLLER_H
#define MAINTABSTOREITEMCONTROLLER_H

#include <QWidget>
#include "Main/MainTabStoreItem.h"
#include "Document/DocumentInfoModel.h"
#include "Document/StoreDocument/StoreDocumentTVModel.h"
#include "Document/StoreDocument/DocumentPZController.h"
#include "Document/StoreDocument/DocumentWZController.h"
#include "Document/StoreDocument/StorageController.h"
#include "Main/MainTabDocumentItemController.h"
class MainTabStoreItem;

class MainTabStoreItemController : public  MainTabDocumentItemController
{
    Q_OBJECT

private:
    MainTabStoreItem *view;
    StorageService *storageService;
    DocumentWZService *wzService;
    DocumentPZService *pzService;
    void initFilters();
    void initSelectingColumnVisibility();
    void restoreTableState();
    void saveTableState();

public:
    MainTabStoreItemController();
    ~MainTabStoreItemController();
    MainTabItem *getView();
    ModuleManager::Module module();
    void initModel();

public slots:

    void addDocument(const int index);
    void dialogStorePZAdd();
    void dialogStoreWZAdd();
    void dialogStoreRWAdd();
    void dialogStorePWAdd();
    void dialogStoreMMAdd();
    void refreshTabStore();
    void dialogEditStore();
    void dialogDeleteStore();
    void sortByColumn(int column);
    void changeColumnVisiblity(QList<int> visibleColumns);
    void printDocument();

};

#endif // MAINTABSTOREITEMCONTROLLER_H
