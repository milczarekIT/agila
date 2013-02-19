#ifndef POLIFIELDSORTFILTERPROXYMODEL_H
#define POLIFIELDSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class PoliFieldSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
private:
    QString filterSymbol;
    QString filterName;
    QString filterNip;
protected:
    bool filterAcceptsRow(int sourceRow,const QModelIndex &sourceParent) const;
public:
    PoliFieldSortFilterProxyModel(QObject * parent = 0);
public slots:
    void setFilterSymbol(const QString &pattern);
    void setFilterName(const QString &pattern);
    void setFilterNip(const QString &pattern);
};

#endif // POLIFIELDSORTFILTERPROXYMODEL_H
