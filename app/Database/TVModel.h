#ifndef TVMODEL_H
#define TVMODEL_H

#include <QSqlQueryModel>
#include <QVariant>
#include "Database/Database.h"
#include "Goods/Price.h"

/**
  * Model dla TableView
  * @author Bartosz Milczarek
  */
class TVModel : public QSqlQueryModel
{
protected:
    virtual void initHeaders() = 0;

    Database *database;
    Qt::SortOrder sortOrder;
    int sortColumn;
public:
    TVModel();
    ~TVModel();

    Qt::SortOrder getSortOrder();
    int getSortColumn();
    QVariant baseData(const QModelIndex & index, int role) const;
};

#endif // TVMODEL_H
