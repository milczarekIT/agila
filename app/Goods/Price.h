#ifndef PRICE_H
#define PRICE_H

#include <QString>
#include <QRegExp>

class Price
{
private:
    double val;
public:
    Price();
    Price(double val);
    ~Price();

    // price types
    static const int A = 0;
    static const int B = 2;
    static const int C = 4;
    static const int MAG = 6;
    static const int ABC = 7;

    static const int NET = 0;
    static const int GROSS = 1;

    double value();
    QString toString();

    void operator = (Price price);
    void operator = (double value);

    static QString priceLevelToString(int priceLevel);
    static int priceLevelToInt(QString priceLevelString);


};

#endif // PRICE_H
