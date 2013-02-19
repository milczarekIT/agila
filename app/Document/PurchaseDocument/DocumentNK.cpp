#include "DocumentNK.h"

DocumentNK::DocumentNK()
{
    this->documentType = "NK";
}

void DocumentNK::setInvoiceSymbol(QString invoiceSymbol) { this->invoiceSymbol = invoiceSymbol; }
void DocumentNK::setInvoiceDate(QDate invoiceDate) { this->invoiceDate = invoiceDate; }
void DocumentNK::setCorrectedContent(QString correctedContent) { this->correctedContent = correctedContent; }
void DocumentNK::setCorrectContent(QString correctContent) { this->correctContetnt = correctContent; }

QString DocumentNK::getInvoiceSymbol() { return invoiceSymbol; }
QDate DocumentNK::getInvoiceDate() { return invoiceDate; }
QString DocumentNK::getCorrectedContent() { return correctedContent; }
QString DocumentNK::getCorrectContent() { return correctContetnt; }

int DocumentNK::operator ==(DocumentNK nk)
{
    if(this->documentSymbol != nk.getSymbol())
        return 0;
    else if(this->documentDate != nk.getDocumentDate())
        return 0;
    else if(this->documentPlace != nk.getDocumentPlace())
        return 0;
    else if(this->invoiceSymbol != nk.getInvoiceSymbol())
        return 0;
    else if(this->invoiceDate != nk.getInvoiceDate())
        return 0;
    else if(this->contractor.getId() != nk.getContractor().getId())
        return 0;
    else if(this->correctedContent != nk.getCorrectedContent())
        return 0;
    else if(this->correctContetnt != nk.getCorrectContent())
        return 0;
    else if(this->issueName != nk.getIssueName())
        return 0;
    else if(this->receiveName != nk.getReceiveName())
        return 0;
    else
        return 1;
}
