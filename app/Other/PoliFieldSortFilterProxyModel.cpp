#include "PoliFieldSortFilterProxyModel.h"
#include <QDebug>

PoliFieldSortFilterProxyModel::PoliFieldSortFilterProxyModel( QObject * parent): QSortFilterProxyModel(parent)
{
    filterSymbol="";
    filterName="";
    filterNip="";
}

bool PoliFieldSortFilterProxyModel::filterAcceptsRow(int sourceRow,
         const QModelIndex &sourceParent) const
 {
     QModelIndex index0 = sourceModel()->index(sourceRow, 1, sourceParent);
     QModelIndex index1 = sourceModel()->index(sourceRow, 2, sourceParent);
     QModelIndex index2 = sourceModel()->index(sourceRow, 6, sourceParent);
     return (sourceModel()->data(index0).toString().startsWith(filterSymbol)
             && sourceModel()->data(index1).toString().startsWith(filterName)
            && sourceModel()->data(index2).toString().startsWith(filterNip));
 }
void PoliFieldSortFilterProxyModel::setFilterSymbol(const QString &pattern){
filterSymbol=pattern;
invalidateFilter();
}
void PoliFieldSortFilterProxyModel::setFilterName(const QString &pattern){
filterName=pattern;
invalidateFilter();
}
void PoliFieldSortFilterProxyModel::setFilterNip(const QString &pattern){
    filterNip=pattern;
    invalidateFilter();
}
