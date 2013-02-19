#ifndef MAINTABGOODSITEMCONTROLLER_H
#define MAINTABGOODSITEMCONTROLLER_H

#include <QWidget>
#include "Goods/GoodsService.h"
#include "Goods/GoodsTVModel.h"
#include "Goods/GoodsRemoveConfirmativeDialog.h"
#include "Main/MainTabGoodsItem.h"
#include "Main/MainTabItemController.h"
#include "Goods/GoodsDialogController.h"
#include "Other/TableStateManager.h"
#include "Other/ITableStateManager.h"
#include "SelectionWindows/SelectVisibleColumns.h"
class MainTabGoodsItem;

class MainTabGoodsItemController : public MainTabItemController, public ITableStateManager
{
    Q_OBJECT

private:
    MainTabGoodsItem *view;
    GoodsService *goodsService;
    GoodsTVModel *model;
    TableStateManager *tableStateManager;
    SelectVisibleColumns *selectColumnsDialog;
    void fillBox(QComboBox *box,QVector<GoodsGroup> values);
    void initComboBox();
    void initPriceFilter();
    int getVisiblePriceLevel();
    void restoreTableState();
    void saveTableState();
    void initSelectingColumnVisibility();

    /** Ustawia widoczne kolumny w tableView o podanym typie cen, pozostałe ustawia jako niewidoczne */
    void setVisiblePriceLevel(int priceType);

public:
    MainTabGoodsItemController();
    ~MainTabGoodsItemController();
    MainTabItem *getView();
    GoodsTVModel *getModel();
    void initModel();
    void refreshTable();

    ModuleManager::Module module();

public slots:
    void dialogGoodsAdd();
    void removeGood();
    void setGoodsNameFilter (QString filter);
    void setGoodsSymbolFilter (QString filter);
    void setGoodsGroupFilter(int index);
    void setPriceLevelFilter(int index);
    void dialogGoodsEdit();
    void dialogSelectColumns();
    void settingsChanged(const QString element);

private slots:
    void changeColumnVisiblity(QList<int> visibleColumns);

signals:
    void settingsChangedSignal(const QString element);

};

#endif // MAINTABGOODSITEMCONTROLLER_H
