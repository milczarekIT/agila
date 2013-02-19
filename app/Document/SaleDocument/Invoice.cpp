#include "Invoice.h"

Invoice::Invoice()
{
    paid = true;
    total = 0.0;
    storeResult = true;
    paymentDate = QDate::currentDate();
    saleDate = QDate::currentDate();
    orderSymbol = "";
}

void Invoice::setMethodOfPayment(MethodOfPayment mop)
{
    this->methodOfPayment = mop;
    paymentDate = documentDate.addDays(mop.getMaturity());
}

void Invoice::setSaleDate(QDate saleDate)
{
    this->saleDate = saleDate;
}
void Invoice::setPaymentDate(QDate paymentDate)
{
    this->paymentDate = paymentDate;
}

void Invoice::setPaid(bool paid)
{
    this->paid = paid;
}
void Invoice::setDiscount(double discount)
{
    this->discount = discount;
}
void Invoice::setOrder(QString orderSymbol) {
    this->orderSymbol = orderSymbol;
}

void Invoice::updateTotal(double update)
{
    this->total += update;
}

MethodOfPayment Invoice::getMethodOfPayment()
{
    return methodOfPayment;
}
QDate Invoice::getDocumentDate()
{
    return documentDate;
}

QDate Invoice::getSaleDate()
{
    return saleDate;
}
QDate Invoice::getPaymentDate()
{
    return paymentDate;
}
bool Invoice::isPaid()
{
    return paid;
}
double Invoice::getDiscount()
{
    return discount;
}

QString Invoice::getOrder() {
    return orderSymbol;
}

QString Invoice::toString()
{
   return  QString("1) Symbol: ").append(this->getSymbol())
           + QString(", 3) Miejsce wystawienia dokumentu: ").append(this->getDocumentPlace())
           + QString(", 4) Sposob zapłaty: ").append(this->getMethodOfPayment().getName())
           + QString(", 5) Kontrahent id: ").append(QVariant(this->getContractor().getId()).toString())
           + QString(", 6) Data wystawienia dokumentu: ").append(this->getDocumentDate().toString("yyyy-MM-dd"))
           + QString(", 6) Data sprzedaży: ").append(this->getSaleDate().toString("yyyy-MM-dd"))
           + QString(", 7) Data zapłaty: ").append(this->getPaymentDate().toString("yyyy-MM-dd"))
           + QString(", 8) Czy zapłacone: ").append(QVariant(this->isPaid()).toString())
           + QString(", 9) Skutek magazynowy: ").append(QVariant(this->storeResult).toString())
           + QString(", 10) Nr zamówienia: ").append(this->orderSymbol)
           + QString(", 11) Rabat: ").append(QVariant(this->getDiscount()).toString())
           + QString(", 12) Wartość: ").append(QVariant(this->getTotal()).toString()) + positionsToString();


}

int Invoice::operator ==(Invoice in)
{
    if(this->methodOfPayment.getId() != in.getMethodOfPayment().getId())
       return 0;
     else if(!(this->contractor == in.getContractor()))
        return 0;
    else if(this->saleDate != in.getSaleDate())
       return 0;
    else if(this->paymentDate != in.getPaymentDate())
        return 0;
    else if(this->paid!= in.isPaid())
       return 0;
    else if(this->discount != in.getDiscount())
        return 0;
    else if(this->orderSymbol != in.getOrder())
        return 0;
    else if (this->documentSymbol !=in.getSymbol())
        return 0;
    else if(this->documentPositions != in.getDocumentPositions())
        return 0;
    else if(this->documentPlace != in.getDocumentPlace())
        return 0;
    else if(this->documentDate != in.getDocumentDate())
        return 0;
    else if(this->issueName != in.getIssueName())
        return 0;
    else if(this->receiveName != in.getReceiveName())
        return 0;
    else if(this->storeResult != in.getStoreResult())
        return 0;
    else if(!(this->total-in.getTotal()<=0.0001 && this->total - in.getTotal() >= -0.0001))
       return 0;
    else
        return 1;
}
