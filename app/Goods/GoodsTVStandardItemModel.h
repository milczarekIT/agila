#ifndef GOODSTVSTANDARDITEMMODEL_H
#define GOODSTVSTANDARDITEMMODEL_H

#include <QSqlQuery>
#include <QStandardItemModel>
#include "Database/Database.h"
#include "Goods/GoodsFilters.h"
#include "Other/Application/ApplicationManager.h"

class GoodsTVStandardItemModel : public QStandardItemModel, public GoodsFilters
{
    Q_OBJECT
private:
    QSqlQuery *query;
    Qt::SortOrder sortOrder;
    int sortColumn;

    void initHeaders(int off);
    QStandardItem *createCheckedItem();
    QStandardItem *createItem(QString value);
    void initData(QSqlQuery *query);

public:
    explicit GoodsTVStandardItemModel(QObject *parent = 0);
    void *getGoods();
    Qt::SortOrder getSortOrder();
    int getSortColumn();
    bool containsId(QString id);
    int clearUnchecked();
    bool isUncheckedItem(int row, int col = 1);
    bool isCheckedItem(int row, int col = 1);

signals:
    
public slots:
    
};

#endif // GOODSTVSTANDARDITEMMODEL_H
