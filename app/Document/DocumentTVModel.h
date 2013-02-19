#ifndef DOCUMENTTVMODEL_H
#define DOCUMENTTVMODEL_H

#include "Database/TVModel.h"
#include "Document/DocumentTVDisplayer.h"

class DocumentTVModel : public TVModel
{
private:
    bool isSymbolSortOrder();
protected:
    QString docTypeFilter;
    QString docNotTypeFilter;
    QString fromDateFilter;
    QString toDateFilter;
    QString sortOrdering;
    QString symbolFilter;

    virtual void initHeaders() = 0;

    QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;


public:
    DocumentTVModel();
    ~DocumentTVModel();
    void sortByColumn ( int column, Qt::SortOrder order = Qt::AscendingOrder );

    virtual void getDocuments() = 0;

    void setDocTypeFilter(QString value);
    void setDocTypeFilter(QStringList value);
    void setDocNotTypeFilter(QString value); // wyklucza typy dokumentów o podanym parametrze
    void setFromDateFilter(QDate fromDate);
    void setToDateFilter(QDate toDate);
    void setSymbolFilter(QString value);
};

#endif // DOCUMENTTVMODEL_H
