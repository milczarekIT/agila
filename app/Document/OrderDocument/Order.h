#ifndef ORDER_H
#define ORDER_H

#include "Document/Document.h"

/**
  * Zamówienie (od klienta, do dostawcy)
  * @author Bartosz Milczarek
  */
class Order : public Document
{
    QDate realizationDate;
    double discount;
    bool realized;
public:
    int operator ==(Order order);
    Order();
    void setRealizationDate(QDate realizationDate);
    void setDiscount(double discount);
    void setRealized(bool realized);

    QDate getRealizationDate();
    double getDiscount();
    bool isRealized();
};

#endif // ORDER_H
