#include "DocumentTVDisplayer.h"

DocumentTVDisplayer::DocumentTVDisplayer(const QModelIndex & index, int role, TVModel const* model) : TVDisplayer(index, role, model)
{
}

DocumentTVDisplayer::~DocumentTVDisplayer()
{

}

QVariant DocumentTVDisplayer::display() const
{
    if (isDisplayOrEditRole())
       {
           if(isValueColumn())
               return displayValue();
           else if(isDateColumn())
               return displayDate();
           else
               return model->baseData(index, role);
       }
       if(role == Qt::TextAlignmentRole)
       {
           if(isValueColumn())
               return QVariant(Qt::AlignRight | Qt::AlignVCenter);
           if(isDateColumn())
               return QVariant(Qt::AlignCenter | Qt::AlignVCenter);
           if(isDocumentTypeColumn())
               return QVariant(Qt::AlignCenter | Qt::AlignVCenter);
       }
       return QVariant();
}

bool DocumentTVDisplayer::isDocumentTypeColumn() const {
    return index.column() == 1;
}

bool DocumentTVDisplayer::isValueColumn() const {
    return index.column() == 7;
}
bool DocumentTVDisplayer::isSymbolColumn() const {
    return index.column() == 3;
}
bool DocumentTVDisplayer::isNameColumn() const {
    return index.column() == 4;
}
bool DocumentTVDisplayer::isDateColumn() const {
    return (index.column() == 5 || index.column() == 6);
}

QVariant DocumentTVDisplayer::displayValue() const {
    double value = model->baseData(index, role).toDouble();

    return QString::number(value, ',', 2).replace(QRegExp("[.]"), ",");
}

QVariant DocumentTVDisplayer::displayDate() const {
    QDate date = model->baseData(index, role).toDate();

    return date.toString("dd-MM-yyyy");
}

