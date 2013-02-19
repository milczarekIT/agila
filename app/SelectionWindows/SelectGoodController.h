#ifndef SELECTGOODCONTROLLER_H
#define SELECTGOODCONTROLLER_H

#include <QVector>
#include "Components/TableView.h"
#include "Goods/Goods.h"
#include "Goods/GoodsTVModel.h"
#include "SelectionWindows/SelectGoodView.h"
#include "Goods/GoodsDialogView.h"
#include "SelectionWindows/SelectionNumberOfGoodsController.h"
#include "SelectionWindows/SelectVisibleColumns.h"
#include "Other/TableStateManager.h"
#include "Other/ITableStateManager.h"

class SelectGoodView;

class SelectGoodController : public QObject, public ITableStateManager {
    Q_OBJECT

private:
    SelectionNumberOfGoodsController* dialogQuantity;
    int cancel;

    TableView* goodsTable;

    GoodsTVModel *goodsTVModel;
    GoodsService *goodsService;
    SelectVisibleColumns *selectColumnsDialog;
    /**
    Metoda prywatna odpowiedzialna za edycje towaru z poziomu okna wyboru towaru dla faktury
    */
    void editGood(int id=0);

    int getQuantityColumn();

    void restoreTableState();
    void saveTableState();

protected:
    SelectGoodView* view;
    QString symbol;
    virtual void initGoodsTable();
    virtual void initStartConf();

public:

    SelectionNumberOfGoodsController* getDialogQuantity();
    int getCancel();
    QString getSymbol();
    SelectGoodView * getView();

    SelectGoodController(QWidget* parent, QString symbol);
    SelectGoodController();
    ~SelectGoodController();

    void showDialog();
    void fillBox(QComboBox *box, QVector<GoodsGroup> values);
    void initFilters();
    /**
    Metoda publiczna odpowiedzialna za dodanie wybranego towaru do okna faktury.
    */
    Goods addGood();
    GoodsTVModel *getGoodsTVModel();
    GoodsService *getGoodsService();

public slots:
    virtual void selectGoods();
    void dialogGoodAdd();
    void setCancel();
    void dialogGoodsEdit();
    void dialogSelectColumns();
    void changeColumnVisiblity(QList<int> visibleColumns);

    virtual void setGoodsNameFilter(QString text);
    virtual void setGoodsSymbolFilter(QString text);
    virtual void setGoodsGoodGroupFilter(int id);
    virtual void setTaxForRRFilter(int idTax);
    virtual void markAllItems(bool mark);
    virtual void showingMarkAll(int count);

signals:
    void rowCountChanged(const int count);
 };

#endif // SELECTGOODCONTROLLER_H
