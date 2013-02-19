#ifndef Invoice_H
#define Invoice_H

#include <QString>
#include <QVector>
#include <QVariant>
#include <QDateEdit>
#include "Document/Document.h"
#include "Contractor/Contractor.h"

class Invoice : public Document
{
protected:
    MethodOfPayment methodOfPayment;
    QDate saleDate;
    QDate paymentDate;  // po wybraniu odpowiedniego sposobu płatności ustawiania jest data zapłaty
    bool paid;
    double discount;
    QString orderSymbol;

public:
    Invoice();
    void setMethodOfPayment(MethodOfPayment mop);
    void setSaleDate(QDate saleDate);
    void setPaymentDate(QDate paymentDate);
    void setPaid(bool paid);
    void setDiscount(double discount);
    void setOrder(QString orderSymbol = " ");
    void updateTotal(double update);

    MethodOfPayment getMethodOfPayment();
    QDate getDocumentDate();
    QDate getSaleDate();
    QDate getPaymentDate();
    bool isPaid();
    double getDiscount();
    QString getOrder();
    QString toString();
    int operator==(Invoice c);
};

#endif // Invoice_H
