#ifndef TVDISPLAYER_H
#define TVDISPLAYER_H

#include <QVariant>
#include <QModelIndex>
#include "Database/TVModel.h"
#include "Database/Model.h"


/**
  * Displayer customowych danych dla TableView
  * @author Bartosz Milczarek
  */
class TVDisplayer
{
protected:
    QModelIndex index;
    int role;
    TVModel const* model;
    int COL_ID;

    bool isDisplayOrEditRole() const;
    bool isTextAligmentRole() const;

    /** pobiera dane z podanej w @param numerze */
    QVariant getCellDataAtCol(int column) const;
public:
    TVDisplayer(const QModelIndex & index, int role, TVModel const* model);
    ~TVDisplayer();

    /** zwraca wyświetlaną wartość */
    virtual QVariant display() const = 0;
};

#endif // TVDISPLAYER_H
