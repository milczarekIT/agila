#ifndef CASHDOCUMENT_H
#define CASHDOCUMENT_H

#include "Document/Document.h"
#include "Document/SaleDocument/Invoice.h"

/**
  * Dokument KP - Kasa przyjmie / Kasa Przyjęła
  * Klasa dziedziczy z Document: documentSymbol, total, Contractor, issueName, receiveName, document place, documentDate
  */
class CashDocument : public Document
{
private:
    QDate paymentDate;
    QString title;
    QString description;
    QString baseDocumentSymbol; // symbol faktury, paragonu którego dotyczy wpłata

public:
    CashDocument();
    CashDocument(Invoice fv);

    void setPaymentDate(QDate paymentDate);
    void setTitle(QString title);
    void setDescription(QString desciption);
    void setBaseDocumentSymbol(QString baseDocumentSymbol);

    QDate getPaymentDate();
    QString getTitle();
    QString getDescription();
    QString getBaseDocumentSymbol();

    QString toString();
    int operator ==(CashDocument kp);
};

#endif // CASHDOCUMENT_H
