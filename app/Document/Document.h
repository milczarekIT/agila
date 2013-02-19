#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QString>
#include <QVector>
#include <QDate>
#include <QStringList>
#include "Goods/Goods.h"
#include "Document/DocumentPosition.h"
#include "Document/MethodOfPayment.h"
#include "Contractor/Contractor.h"
#include "Document/SimpleDocumentInfo.h"
#include "Other/Owner/OwnerService.h"

class Document  {

protected:
    QString documentSymbol;
    QString documentPlace;       //miejsce wystawienia dokumentu
    QDate documentDate;  //data wystawienia dokumentu
    QString issueName;  //nazwa osoby, która wystawiła dokument
    QString receiveName;//nazwa osoby, ktora przyjeła towar
    QVector<DocumentPosition> documentPositions;
    bool storeResult;
    double total;
    Contractor contractor;
    int ownerId; // id podmiotu/właściciela

    QVector<SimpleDocumentInfo> relatedDocuments;

    QString positionsToString();

    // document info
    QString documentName; // np. Faktura VAT
    QString documentType; // np. FV
    QString documentFamily; // np. Dokumenty sprzedaży
    QString signature; //podpis pod dokumentem


public:
    Document();

    QString getSymbol();
    QString getDocumentPlace();
    QDate getDocumentDate();
    QString getIssueName();
    QString getReceiveName();
    QVector<DocumentPosition> getDocumentPositions();
    bool getStoreResult();
    double getTotal();
    Contractor getContractor();
    QVector<SimpleDocumentInfo> getRelatedDocuments();
    int getOwnerId();

    QString getDocumentName();
    QString getDocumentType();
    QString getDocumentFamily();
    QString getSignature();

    void setSymbol(QString symbol);
    void setDocumentPlace(QString documentPlace);
    void setDocumentDate(QDate documentDate);
    void setDocumentPositions(QVector<DocumentPosition> documentPositions);
    void setStoreResult(bool storeResult);
    void setTotal(double total);
    void setContractor(Contractor contractor);
    void setIssueName(QString issueName);
    void setReceiveName(QString receiveName);
    void setRelatedDocuments(QVector<SimpleDocumentInfo> relatedDocuments);
    void setOwnerId(int ownerId);

    void setDocumentName(QString documentName);
    void setDocumentType(QString documentType);
    void setDocumentFamily(QString documentFamily);


    QString toString();

};

#endif // DOCUMENT_H
