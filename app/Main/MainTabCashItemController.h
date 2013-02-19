#ifndef MAINTABCASHITEMCONTROLLER_H
#define MAINTABCASHITEMCONTROLLER_H

#include <QWidget>
#include "Main/MainTabCashItem.h"
#include "Document/CashDocument/CashDocumentController.h"
#include "Document/CashDocument/CashDocumentTVModel.h"
#include "Main/MainTabDocumentItemController.h"
class MainTabCashItem;

class MainTabCashItemController : public MainTabDocumentItemController
{
    Q_OBJECT

private:
    MainTabCashItem *view;
    CashDocumentService *service;
    void initFilters();
    void initSelectingColumnVisibility();
    void restoreTableState();
    void saveTableState();

public:
    explicit MainTabCashItemController();
    ~MainTabCashItemController();
    MainTabItem *getView();
    CashDocumentTVModel *getModel();
    ModuleManager::Module module();

public slots:
    void addDocument(const int index);
    void dialogDocumentKPAdd();
    void dialogDocumentKWAdd();
    void dialogDocumentEdit();
    void documentRemove();
    void initModel();
    void sortByColumn(int column);
    void changeColumnVisiblity(QList<int> visibleColumns);
    void printDocument();

};

#endif // MAINTABCASHITEMCONTROLLER_H
