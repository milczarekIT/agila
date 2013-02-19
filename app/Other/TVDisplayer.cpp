#include "TVDisplayer.h"

TVDisplayer::TVDisplayer(const QModelIndex & index, int role, TVModel const* model)
{
    this->index = index;
    this->role = role;
    this->model = model;
    COL_ID = 0;
}

TVDisplayer::~TVDisplayer() {

}

bool TVDisplayer::isDisplayOrEditRole() const {
    return role == Qt::DisplayRole || role == Qt::EditRole;
}

bool TVDisplayer::isTextAligmentRole() const {
    return role == Qt::TextAlignmentRole;
}

QVariant TVDisplayer::getCellDataAtCol(int column) const {
    return index.model()->data(index.model()->index(index.row(),column));
}
