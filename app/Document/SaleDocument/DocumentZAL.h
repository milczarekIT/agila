#ifndef DOCUMENTZAL_H
#define DOCUMENTZAL_H

#include "Document/SaleDocument/Invoice.h"

class DocumentZAL : public Invoice
{
    QVector<SimpleDocumentInfo> previousDocumentsZAL;
    double paidValue; // wpłacona kwota (zaliczka)
public:
    DocumentZAL();

    void setPreviousDocumentsZAL(QVector<SimpleDocumentInfo> previousDocumentsZAL);
    QVector<SimpleDocumentInfo> getPreviousDocumentsZAL();

    void setPaidValue(double paidValue);
    double getPaidValue();
    int operator ==(DocumentZAL in);

};

#endif // DOCUMENTZAL_H
