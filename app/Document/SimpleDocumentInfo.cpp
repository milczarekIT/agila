#include "SimpleDocumentInfo.h"

SimpleDocumentInfo::SimpleDocumentInfo()
{
    total = 0.0;
    type = "";
    symbol = "";
    documentDate.setDate(0, 0, 0);
}

void SimpleDocumentInfo::setType(QString type) {
    this->type = type;
}

void SimpleDocumentInfo::setSymbol(QString symbol) {
    this->symbol = symbol;
}

void SimpleDocumentInfo::setDocumentDate(QDate documentDate) {
    this->documentDate = documentDate;
}

void SimpleDocumentInfo::setTotal(double total) {
    this->total = total;
}

QString SimpleDocumentInfo::getType() {
    return this->type;
}

QString SimpleDocumentInfo::getSymbol() {
    return this->symbol;
}

QDate SimpleDocumentInfo::getDocumentDate() {
    return this->documentDate;
}

double SimpleDocumentInfo::getTotal() {
    return this->total;
}

bool SimpleDocumentInfo::operator==(SimpleDocumentInfo sdi)
{
    if(this->type != sdi.getType())
        return false;
    else if(this->symbol != sdi.getSymbol())
        return false;
    else if(this->documentDate != sdi.getDocumentDate())
        return false;
    else if(this->total != sdi.getTotal())
        return false;
    else
        return true;
}

QString SimpleDocumentInfo::toString() {
    return type.append(QString(" | "))
            .append(symbol).append(QString(" | "))
            .append(documentDate.toString("yyyy-MM-dd"))
            .append(QString(" | "))
            .append(QVariant(total).toString());
}
