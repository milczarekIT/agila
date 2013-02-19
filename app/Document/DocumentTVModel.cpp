#include "DocumentTVModel.h"

DocumentTVModel::DocumentTVModel() : TVModel()
{
    sortColumn=1;
    sortOrder=Qt::AscendingOrder;
    docTypeFilter = "";
    docNotTypeFilter = "";
    fromDateFilter = "";
    toDateFilter = "";
    sortOrdering = "";
    symbolFilter = "";
}

DocumentTVModel::~DocumentTVModel() {

}

void DocumentTVModel::sortByColumn ( int column, Qt::SortOrder order)
{
    this->sortColumn=column+1;
    this->sortOrder=order;
    QString sortNameTemp = ((sortOrder==Qt::AscendingOrder) ? "DESC" : "ASC");
    if(this->isSymbolSortOrder())
    {
        this->sortOrdering = "ORDER BY type " + sortNameTemp + ", id " + sortNameTemp + " "; // po symbolu tzn. po typie a potem po id
    }
    else
        this->sortOrdering = "ORDER BY "+QString::number(sortColumn)+" "+((sortOrder==Qt::AscendingOrder) ? "DESC" : "ASC") + " "; // tradycyjne sortowanie
    getDocuments();
}

bool DocumentTVModel::isSymbolSortOrder() {
    return (sortColumn == 3);
}

QVariant DocumentTVModel::data ( const QModelIndex & index, int role ) const
{
    DocumentTVDisplayer displayer(index, role, this);
    return displayer.display();
}

void DocumentTVModel::setDocTypeFilter(QString value)
{
    if(value.isEmpty())
        docTypeFilter = "";
    else
        docTypeFilter = "AND type LIKE '" + value + "' ";
}

void DocumentTVModel::setDocTypeFilter(QStringList value)
{
    if(value.size() == 0)
        docTypeFilter = "";
    else
    {
        docTypeFilter = "AND (";
        docTypeFilter.append("type LIKE '" + value.at(0) + "' ");
        for(int i = 1; i < value.size(); i++)
        {
            docTypeFilter.append("OR type LIKE '" + value.at(i) + "' ");
        }
        docTypeFilter.append(") ");

    }
}

void DocumentTVModel::setDocNotTypeFilter(QString value)
{
    if(value.isEmpty())
        docNotTypeFilter = "";
    else
        docNotTypeFilter = "AND type NOT LIKE '" + value + "' ";
}

void DocumentTVModel::setFromDateFilter(QDate fromDate)
{
    fromDateFilter = "AND document_date >= '" + fromDate.toString("yyyy-MM-dd") + "' ";
}

void DocumentTVModel::setToDateFilter(QDate toDate)
{
    toDateFilter = "AND document_date <= '" + toDate.toString("yyyy-MM-dd") + "' ";
}

void DocumentTVModel::setSymbolFilter(QString value)
{
    if(value.isEmpty())
        symbolFilter = "";
    else
        symbolFilter = "AND UPPER(symbol) LIKE '" + value.toUpper() + "%' ";
}


