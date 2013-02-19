#ifndef METHODOFPAYMENT_H
#define METHODOFPAYMENT_H

#include <QString>
#include <QVariant>
#include "Other/SimpleStructure.h"

class MethodOfPayment : public SimpleStructure
{
private:
    int maturity;
public:
    MethodOfPayment();
    MethodOfPayment(QString name, int maturity);
    MethodOfPayment(int id,QString name, int maturity);

    void setMaturity(int maturity);

    int getMaturity();

    QString toString();
    int operator==(MethodOfPayment mop);
};

#endif // METHODOFPAYMENT_H
