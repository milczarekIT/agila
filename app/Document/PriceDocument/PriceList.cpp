#include "PriceList.h"

PriceList::PriceList() : Document()
{
    documentDate = QDate::currentDate();
}

QString PriceList::getDescribe() {
    return describe;
}

QDate PriceList::getValidFromDate() {
    return validFromDate;
}

QDate PriceList::getValidToDate() {
    return validToDate;
}

void PriceList::setDescribe(QString describe) {
    this->describe = describe;
}

void PriceList::setValidFromDate(QDate validFromDate) {
    this->validFromDate = validFromDate;
}

void PriceList::setValidToDate(QDate validToDate) {
    this->validToDate = validFromDate;
}

QString PriceList::toString() {

    return  QString("1) Symbol: ").append(this->getSymbol())
            + QString(" 2) Nazwa: ").append(this->getDocumentName())
            + QString(" 3) Opis: ").append(this->getDescribe())
            + QString(", 4) Data wystawienia dokumentu: ").append(this->getDocumentDate().toString("yyyy-MM-dd"))
            + QString(", 5) Ważne od: ").append(this->getValidFromDate().toString("yyyy-MM-dd"))
            + QString(", 6) Ważne do: ").append(this->getValidToDate().toString("yyyy-MM-dd"));
}

bool PriceList::operator ==(PriceList list) {
    if(this->getDocumentName() != list.getDocumentName())
        return false;
    if(this->getSymbol() != list.getSymbol())
        return false;
    if(this->getDescribe() != list.getDescribe())
        return false;
    if(this->getDocumentDate() != list.getDocumentDate())
        return false;
    if(this->getValidFromDate() != list.getValidFromDate())
        return false;
    if(this->getValidToDate() != list.getValidToDate())
        return false;
    if(this->getContractor().getId() != list.getContractor().getId())
        return false;
    if(!areDocumentsPositionsEqual(list.getDocumentPositions()))
        return false;
    return true;
}

bool PriceList::areDocumentsPositionsEqual(QVector<DocumentPosition> dp) {
    if(getDocumentPositions().size() != dp.size()) return false;

    for(int i = 0; i < dp.size(); i++) {
        if(dp[i].getGood().getId() !=
                 getDocumentPositions()[i].getGood().getId())
                 return false;
    }
    return true;
}
