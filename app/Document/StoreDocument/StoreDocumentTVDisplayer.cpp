#include "StoreDocumentTVDisplayer.h"

StoreDocumentTVDisplayer::StoreDocumentTVDisplayer(const QModelIndex & index, int role, TVModel const* model) : TVDisplayer(index, role, model)
{
}

StoreDocumentTVDisplayer::~StoreDocumentTVDisplayer()
{
}

QVariant StoreDocumentTVDisplayer::display() const {

    if (isDisplayOrEditRole())
    {
        if(isValueColumn())
        {
            double value = model->baseData(index, role).toDouble();

            return QString::number(value, ',', 2).replace(QRegExp("[.]"), ",");
        }
        else
        {
            return model->baseData(index, role);
        }
    }
    if(this->isTextAligmentRole())
    {
        if (isValueColumn())
                return QVariant(Qt::AlignRight | Qt::AlignVCenter);
    }
    return QVariant();
}

bool StoreDocumentTVDisplayer::isValueColumn() const {
    return index.column() == 2;
}
