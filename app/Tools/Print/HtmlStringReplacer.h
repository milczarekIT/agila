#ifndef HTMLSTRINGREPLACER_H
#define HTMLSTRINGREPLACER_H

#include <QString>
#include "Document/DocumentPosition.h"
#include "Document/SimpleDocumentInfo.h"
#include "Contractor/Contractor.h"
#include "Other/Owner/Owner.h"
#include "Document/DocumentInfoModel.h"

class HtmlStringReplacer : public QObject
{
    Q_OBJECT

public:
    HtmlStringReplacer();

    QString htmlCode;
    bool isNet;
    QString symbol;

    void setCopyOrOriginal(QString copyOrOriginal);
    void setMyCompany(Owner data);
    void setLogoPathOwner(QString logoPath);
    void setIssuePlace(QString data);
    void setPriceOption(QString data, bool type);
    void setSaleDate(QString data);
    void setIssueDate(QString data);
    void setPaymentDate(QString data);
    void setSellerInfo(QString data);
    void setBuyerInfo(Contractor  data);
    void setBuyerInfo(Owner data);
    void setMethodOfPayment(QString data);
    void setDocumentName(QString data);
    void setStoreDate(QString data);
    void setTransport(QString data);
    void setShipping(QString data);
    void setWaybill(QString data);
    void setDocumentNumer(QString data);
    void setSummaryValue (double data);
    void setSummaryValueWord(QString data);
    void setWord(QString data);
    void setDocTypeComment (QString data);
    void setIssueName (QString data);
    void setRole1(QString data);
    void setRole2(QString data);
    void setReceiverName (QString data);
    void setSignature(QString type);
    void setToPay(double data);
    void setToPayWords(QString data);
    //tylko dla NK
    void setInvoiceSymbol(QString data);
    void setInvoiceSaleDate(QString data);
    void setInvoiceIssueDate(QString data);
    void setCorrectedContent (QString data);
    void setCorrectContent (QString data);
    void setSymbol(QString symbol);
    void setRealizationDate(QString data);
};

#endif // HTMLSTRINGREPLACER_H
