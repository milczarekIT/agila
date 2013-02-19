#include "PurchaseDocumentTVDisplayer.h"

PurchaseDocumentTVDisplayer::PurchaseDocumentTVDisplayer(const QModelIndex & index, int role, TVModel const* model) : TVDisplayer(index, role, model)
{
}

PurchaseDocumentTVDisplayer::~PurchaseDocumentTVDisplayer()
{

}

QVariant PurchaseDocumentTVDisplayer::display() const
{
    if (isDisplayOrEditRole())
       {
           if(isValueColumn())
               return displayValue();
           else if (isSymbolColumn())
               return displaySymbol();
           else if (isNameColumn())
                return displayName();
           else if(isPurchaseDateColumn())
               return displayPurchaseDate();
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

bool PurchaseDocumentTVDisplayer::isValueColumn() const {
    return index.column() == 5;
}
bool PurchaseDocumentTVDisplayer::isSymbolColumn() const {
    return index.column() == 1;
}
bool PurchaseDocumentTVDisplayer::isNameColumn() const {
    return index.column() == 2;
}
bool PurchaseDocumentTVDisplayer::isPurchaseDateColumn() const {
    return index.column() == 4;
}

QVariant PurchaseDocumentTVDisplayer::displayValue() const {
    double value = model->baseData(index, role).toDouble();

    QString documentSymbol = this->getCellDataAtCol(0).toString();
    if(documentSymbol.contains("NK/"))
        return QVariant();
    else
        return QString::number(value, ',', 2).replace(QRegExp("[.]"), ",");
}

QVariant PurchaseDocumentTVDisplayer::displayName() const {
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

QVariant PurchaseDocumentTVDisplayer::displaySymbol() const {
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

QVariant PurchaseDocumentTVDisplayer::displayPurchaseDate() const {
    QString documentSymbol = this->getCellDataAtCol(0).toString();
    if(documentSymbol.contains("NK/"))
        return QVariant();
    else
        return model->baseData(index, role).toDate();
}

