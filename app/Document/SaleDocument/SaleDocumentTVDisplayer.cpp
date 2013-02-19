#include "SaleDocumentTVDisplayer.h"

SaleDocumentTVDisplayer::SaleDocumentTVDisplayer(const QModelIndex & index, int role, TVModel const* model) : TVDisplayer(index, role, model)
{
}

SaleDocumentTVDisplayer::~SaleDocumentTVDisplayer()
{

}

QVariant SaleDocumentTVDisplayer::display() const
{
    if (isDisplayOrEditRole())
       {
           if(isValueColumn())
               return displayValue();
           else if (isSymbolColumn())
               return displaySymbol();
           else if (isNameColumn())
                return displayName();
           else
               return model->baseData(index, role);
       }
       if(role == Qt::TextAlignmentRole)
       {
           if (isValueColumn())
                   return QVariant(Qt::AlignRight | Qt::AlignVCenter);
       }
       return QVariant();
}

bool SaleDocumentTVDisplayer::isValueColumn() const {
    return index.column() == 5;
}
bool SaleDocumentTVDisplayer::isSymbolColumn() const {
    return index.column() == 1;
}
bool SaleDocumentTVDisplayer::isNameColumn() const {
    return index.column() == 2;
}

QVariant SaleDocumentTVDisplayer::displayValue() const {
    double value = model->baseData(index, role).toDouble();

    return QString::number(value, ',', 2).replace(QRegExp("[.]"), ",");
}

QVariant SaleDocumentTVDisplayer::displayName() const {
    int id = model->baseData(index, role).toInt();
    if(id != 0) {
        ContractorService *conService = new ContractorService();
        QString name = conService->getContractor(id).getName();
        delete conService;
        return name;
    } else {
        return "";
    }
}

QVariant SaleDocumentTVDisplayer::displaySymbol() const {
    int id = model->baseData(index, role).toInt();
    if(id != 0) {
        ContractorService *conService = new ContractorService();
        QString symbol = conService->getContractor(id).getSymbol();
        delete conService;
        return symbol;
    } else {
        return "";
    }
}

