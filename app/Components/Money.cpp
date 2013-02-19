#include "Money.h"
#include "QDebug"
#include "QVariant"
#include "math.h"
Money::Money(QString Cash)
{
    Cash.remove(QRegExp(" "));
    gold = Cash.section(",",0,0).toLong();
    QString pen = appendZero(Cash.section(",",1,1));
    penny = pen.toLong();
}
Money::Money(){}

Money::Money(long long int gold,long long int penny,bool wasZeroFirst,bool wasBelowZero)
{
    this->wasZeroFirst=wasZeroFirst;
    this->wasBelowZero=wasBelowZero;
    this->penny=penny;
    this->gold = gold;
}

long long int Money::roundPennys(long long int penny)
{
    if(penny<100)
        this->setPenny(penny);
    else
    {
     if(penny>=100)
     {
         int pennys =penny/10;
         int rest = penny % 10;
         if(rest>=5)
         pennys = pennys+1;
         this->setPenny(pennys);
     }

    if(this->penny>=100)
    {
        int pennys =this->penny/10;
        int rest = this->penny % 10;
        if(rest>=5)
        pennys = pennys+1;
        qDebug()<<pennys;
        this->setPenny(pennys);
    }
    if(wasZeroFirst)
    {
        int pennys =this->penny/10;
        int rest = this->penny % 10;
        if(rest>=5)
        pennys = pennys+1;
        this->setPenny(pennys);
    }
   }
    return this->getPenny();
}

long long int Money::countPenny(Money r)
{
    return (r.gold *100)+ r.penny;
}

long long int Money::countPenny()
{
    return (gold*100)+penny;
}

Money Money::operator*(double r)
{
  wasBelowZero=false;
  wasZeroFirst=false;
  long long int newtotal;
  Money cash = doubleWith2Decimal(r);
  newtotal= countPenny() * cash.countPenny();

  QString total = QVariant(newtotal).toString();
  QString rest = total.right(4);
  if(rest.at(0)=='0')
      wasZeroFirst=true;


  return Money(newtotal / 10000, roundPennys(newtotal % 10000), wasZeroFirst);
}

bool Money::getWasZero()
{
    return this->wasZeroFirst;
}
bool Money::getWasBelowZero()
{
    return this->wasBelowZero;
}

Money Money::doubleWith2Decimal(double r)
{
    QString digit = QVariant(r).toString();
    if(digit.section(".",1,1).length()==1)
        digit.append('0');
        digit.replace('.',',');
    return Money(digit);
}

Money Money::operator*(Money r)
{
    wasBelowZero=false;
    wasZeroFirst=false;
    long long int newtotal ;
    newtotal= countPenny() *countPenny(r);

    QString total = QVariant(newtotal).toString();
    QString rest = total.right(4);
    if(rest.at(0)=='0')
        wasZeroFirst=true;

    return Money(newtotal / 10000, roundPennys(newtotal % 10000), wasZeroFirst);
}

Money Money::operator + (Money r)
{
    wasZeroFirst=false;
    wasBelowZero=false;
    long long int newtotal;
    newtotal= countPenny() + countPenny(r);
    QString total = QVariant(newtotal).toString();
    QString rest = total.right(2);
    if(rest.at(0)=='0')
        wasZeroFirst=true;
    return Money(newtotal / 100, newtotal % 100, wasZeroFirst);
}

Money Money::operator - (Money r)
{
    wasZeroFirst=false;
    wasBelowZero=false;
    long long int newtotal ;

    if(countPenny()-countPenny(r)>0 && countPenny()-countPenny(r) <10 )
        wasZeroFirst=true;
    else if (countPenny()-countPenny(r)>-10 && countPenny()-countPenny(r) <-0)
      {
       wasZeroFirst=true;
       wasBelowZero=true;
      }
   else if (countPenny()-countPenny(r)<0)
       wasBelowZero=true;

    newtotal= abs(countPenny() - countPenny(r));
    return Money(newtotal / 100, newtotal % 100,wasZeroFirst,wasBelowZero);

}

QString Money::appendZero(QString cash)
{
    if(cash.length()==1)
       cash.append('0');
       return cash;
}

void Money::operator = (QString Cash)
{
    Cash.remove(QRegExp(" "));
    gold = Cash.section(",",0,0).toLong();
    QString pen = appendZero(Cash.section(",",1,1));
    penny = pen.toLong();

}

void Money::operator =(Money Cash)
{
    this->wasBelowZero=Cash.getWasBelowZero();
    this->wasZeroFirst=Cash.getWasZero();
    this->gold=Cash.gold;
    this->penny=Cash.penny;
}

bool Money::operator ==(Money cash)
{
    return (this->countPenny()==this->countPenny(cash));
}
bool Money::operator <=(Money cash)
{
    return (this->countPenny()<=this->countPenny(cash));
}

bool Money::operator >=(Money cash)
{
    return (this->countPenny()>=this->countPenny(cash));
}
bool Money::operator !=(Money cash)
{
    return (this->countPenny()!=this->countPenny(cash));
}

bool Money::operator <(Money cash)
{
    return (this->countPenny()<this->countPenny(cash));
}

bool Money::operator >(Money cash)
{
    return (this->countPenny()>this->countPenny(cash));
}

long long int Money::getGold()
{
    return this->gold;
}

QString Money::getValue()
{
    QString golds = QVariant(gold).toString();
    QString pennys;
    if(wasZeroFirst)
       pennys='0'+ QVariant(penny).toString();
    else
       pennys = QVariant(penny).toString();

    QString pen = appendZero(pennys);

    if(wasBelowZero)
    return QVariant("-"+golds+","+pen).toString();
    else
    return QVariant(golds+","+pen).toString();
}

void Money::setGold(long long int Gold)
{
    this->gold=Gold;
}

long long int Money::getPenny()
{
    return this->penny;
}
void Money::setPenny(long long int Penny)
{
    this->penny =  Penny;
}
