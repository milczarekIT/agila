#ifndef TABLEVIEW_H
#define TABLEVIEW_H
#include <QtSql>
#include <QKeyEvent>
#include <QTableView>
#include <QModelIndex>
#include <QHeaderView>
#include <QContextMenuEvent>
#include "Database/TVModel.h"
#include "Goods/GoodsTVModel.h"
#include "Contractor/ContractorModel.h"
#include "Menu/TableViewExtendedMenu.h"
#include "Goods/GoodsTVStandardItemModel.h"

class TableView :public QTableView
{
    Q_OBJECT

    TableViewExtendedMenu* tableViewExtendedMenu;
public:
    /**
      * metoda ustawia aktualny model oraz dostosowuje wygląd do widoku kontrahenta
      */
     void setContractorModel (TVModel *model);
     void setGoodsModel (TVModel *model);
     void setSaleDocumentModel (TVModel *model);
     void setOrderDocumentModel (TVModel *model);
     void setPurchaseDocumentModel (TVModel *model);
     void setStoreDocumentModel (TVModel *model);
     void setCashDocumentModel (TVModel *model);
     void setPriceDocumentModel (TVModel *model);
     void setFeatureModel(QSqlQueryModel *model);
     void setGoodsModel(GoodsTVStandardItemModel *goodsTVModel);
     void setMenu();

     void hideIdColumn();

     /**
       * zwraca id kontrahenta w zaznaczonym rzędzie
       */
    int getId();
    int getId(QModelIndex index);
    TableViewExtendedMenu * getExtendedMenu();
    QString getSymbol();
    QString getSymbol(QModelIndex index);
    TableView( QWidget * parent = 0);
    ~TableView();

protected:
    void contextMenuEvent(QContextMenuEvent *event);
};

#endif // TABLEVIEW_H
