#ifndef MAINTABPRICEITEMCONTROLLER_H
#define MAINTABPRICEITEMCONTROLLER_H

#include <QWidget>
#include "Main/MainTabPriceItem.h"
#include "Main/MainTabDocumentItemController.h"
#include "Document/PriceDocument/OfferController.h"
#include "Document/PriceDocument/PriceListController.h"
#include "Document/PriceDocument/PriceDocumentTVModel.h"
class MainTabPriceItem;

class MainTabPriceItemController : public MainTabDocumentItemController
{
    Q_OBJECT
private:
    MainTabPriceItem *view;
    PriceListService *plService;
    void initFilters();
    //float checkAmount();

    void initSelectingColumnVisibility();
    void restoreTableState();
    void saveTableState();

public:
    MainTabPriceItemController();
    ~MainTabPriceItemController();
    MainTabItem *getView();
    ModuleManager::Module module();

public slots:
    void addDocument(const int index);
    void initModel();
    void dialogPriceListAdd();
    void dialogOfferAdd();
    void dialogDocumentEdit();
    void removeDocument();
    /*void changeDisabledMenuActions();
    void issuedFK();
    void issuedKW();
    void issuedKP();*/
    void sortByColumn(int column);
    void changeColumnVisiblity(QList<int> visibleColumns);
    void printDocument();
/*
signals:
    void issuedCashDoc();*/
};

#endif // MAINTABPRICEITEMCONTROLLER_H
