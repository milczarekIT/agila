#ifndef DOCUMENTNK_H
#define DOCUMENTNK_H

#include "Document/Document.h"

/**
  * Nota korygująca (NK)
  * Korzysta z Document: documentSymbol, documentDate
  */
class DocumentNK : public Document
{
    QString invoiceSymbol;
    QDate invoiceDate;

    QString correctedContent; // treść korygowana
    QString correctContetnt; // treść prawidłowa

public:
    DocumentNK();

    void setInvoiceSymbol(QString factureSymbol);
    void setInvoiceDate(QDate factureDate);
    void setCorrectedContent(QString correctedContent); // treść korygowana
    void setCorrectContent(QString correctContent); // treść prawidłowa

    QString getInvoiceSymbol();
    QDate getInvoiceDate();
    QString getCorrectedContent(); // treść korygowana
    QString getCorrectContent(); // treść prawidłowa

    int operator==(DocumentNK nk);
};

#endif // DOCUMENTNK_H
