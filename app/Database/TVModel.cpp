#include "TVModel.h"

TVModel::TVModel()
{
    this->sortColumn = 1;
    this->sortOrder = Qt::AscendingOrder;
}

TVModel::~TVModel() {

}

QVariant TVModel::baseData(const QModelIndex & index, int role) const {
    return QSqlQueryModel::data(index, role);
}

Qt::SortOrder TVModel::getSortOrder(){
    return sortOrder;
}
int TVModel::getSortColumn(){
    return sortColumn;
}

QVariant TVModel::data(int row, int column, int role) {
    return baseData(this->index(row, column), role);
}
