#include "CashDocument.h"

CashDocument::CashDocument()
{
    this->paymentDate = QDate::currentDate();
}

CashDocument::CashDocument(Invoice fv)
{
    this->setContractor(fv.getContractor());
    if(this->documentSymbol.contains("KP"))
        this->setTitle("Wpłata za: " + fv.getSymbol());
    else
        this->setTitle("Wypłata za: " + fv.getSymbol());
    this->setTotal(fv.getTotal());
    this->paymentDate = QDate::currentDate();
    this->baseDocumentSymbol = fv.getSymbol();
}

void CashDocument::setPaymentDate(QDate paymentDate)
{
    this->paymentDate = paymentDate;
}

void CashDocument::setTitle(QString title)
{
    this->title = title;
}

void CashDocument::setDescription(QString description)
{
    this->description = description;
}

void CashDocument::setBaseDocumentSymbol(QString baseDocumentSymbol)
{
    this->baseDocumentSymbol = baseDocumentSymbol;
}

QDate CashDocument::getPaymentDate()
{
    return paymentDate;
}

QString CashDocument::getTitle()
{
    return title;
}

QString CashDocument::getDescription()
{
    return description;
}

QString CashDocument::getBaseDocumentSymbol()
{
    return baseDocumentSymbol;
}

QString CashDocument::toString()
{
    return "1) Symbol: " + this->documentSymbol + " , 2) Kontrahent: " + QVariant(this->getContractor().getId()).toString()
            + ", 3) Data płatności : " + QVariant(this->paymentDate).toString()
            + ", 4) Wpłata: " + QVariant(this->total).toString() + ", 5) Tytułem: " + this->title
            + ", 6) Opis: " + this->description;
}

int CashDocument::operator ==(CashDocument cash)
{
    if(this->baseDocumentSymbol != cash.getBaseDocumentSymbol())
        return 0;
    else if (!(this->contractor == cash.getContractor()))
        return 0;
    else if (this->description != cash.getDescription())
        return 0;
    else if (this->documentDate != cash.getDocumentDate())
        return 0;
    else if (this->documentName != cash.getDocumentName())
        return 0;
    else if (this->documentPlace != cash.getDocumentPlace())
        return 0;
    else if (this->documentType != cash.getDocumentType())
        return 0;
    else if (this->getIssueName() != cash.getIssueName())
        return 0;
    else if (this->getPaymentDate() != cash.getPaymentDate())
        return 0;
    else if (this->getReceiveName() != cash.getReceiveName())
        return 0;
    else if (this->getSymbol() != cash.getSymbol())
        return 0;
    else if (this->getTitle() != cash.getTitle())
        return 0;
    else
        return 1;
}
