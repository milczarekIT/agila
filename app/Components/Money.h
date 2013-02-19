#ifndef MONEY_H
#define MONEY_H

#include <QString>
#include <QRegExp>
class Money
{
public:
    Money(QString Cash);
    Money(long long int gold,long long int penny,bool wasZeroFirst,bool wasBelowZero = 0);
    Money();
    long long int countPenny(Money r);
    long long int countPenny();
    QString appendZero(QString cash);
    Money doubleWith2Decimal(double r);
    long long roundPennys(long long int penny);
    void operator = (QString Cash);
    void operator = (Money Cash);
    Money operator *(Money cash);
    Money operator *(double cash);
    Money operator +(Money cash);
    Money operator -(Money cash);
    bool operator ==(Money cash);
    bool operator <=(Money cash);
    bool operator <(Money cash);
    bool operator >=(Money cash);
    bool operator >(Money cash);
    bool operator !=(Money cash);
    long long int getGold();
    QString getValue();
    void setGold(long long int Gold);
    long long int getPenny();
    void setPenny(long long int Penny);
    bool getWasZero();
    bool getWasBelowZero();
private:
    long long int gold;
    long long int penny;
    long long int sumPenny;
    bool wasZeroFirst;
    bool wasBelowZero;
};



#endif // MONEY_H
