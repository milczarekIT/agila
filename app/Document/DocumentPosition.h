#ifndef DOCUMENTPOSITION_H
#define DOCUMENTPOSITION_H

#include <QString>
#include "Goods/Tax.h"
#include "Goods/Goods.h"

/**
  * Struktura opisujaca pozycję na dokumencie
  */
class DocumentPosition
{
protected:

    Goods good;
    int priceLevel; // np. Price::A
    double quantity;
    double priceNet;
    double priceGross;
    Tax tax;

public:
    DocumentPosition();

    void setPriceLevel(int priceLevel);
    void setGood(Goods good);
    void setQuantity(double quantity);
    void setPriceNet(double priceNet);
    void setPriceGross(double priceGross);
    void setTax(Tax tax);

    Goods getGood();
    double getQuantity();

    /**
        Zwraca ilość w postaci Stringu z uwzględnieniem ilości miejsc po przecinku
        (ilość miejsc po przecinku pobiera z unit)
      */
    QString getQuantityInString();

    double getPriceNet();
    double getPriceGross();
    int getPriceLevel();
    Tax getTax();

    QString toString();

    int operator==(DocumentPosition dp);
};

#endif // DOCUMENTPOSITION_H
