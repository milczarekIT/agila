#include "OrderDocumentTVDisplayer.h"

OrderDocumentTVDisplayer::OrderDocumentTVDisplayer(const QModelIndex & index, int role, TVModel const* model) : TVDisplayer(index, role, model)
{
}

OrderDocumentTVDisplayer::~OrderDocumentTVDisplayer()
{

}

QVariant OrderDocumentTVDisplayer::display() const
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

bool OrderDocumentTVDisplayer::isValueColumn() const {
    return index.column() == 5;
}
bool OrderDocumentTVDisplayer::isSymbolColumn() const {
    return index.column() == 1;
}
bool OrderDocumentTVDisplayer::isNameColumn() const {
    return index.column() == 2;
}

QVariant OrderDocumentTVDisplayer::displayValue() const {
    double value = model->baseData(index, role).toDouble();

    return QString::number(value, ',', 2).replace(QRegExp("[.]"), ",");
}

QVariant OrderDocumentTVDisplayer::displayName() const {
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

QVariant OrderDocumentTVDisplayer::displaySymbol() const {
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

