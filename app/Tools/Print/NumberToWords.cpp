#include "NumberToWords.h"
#include <QDebug>
#include <math.h>
NumberToWords::NumberToWords()
{
}

QString NumberToWords::toWords(double number)
{
    vec.clear();
    words.clear();
    QString WIntegral, WFractional;
    int integral;
    double fractional;

    if(number<0)
    {
        integral = (int)abs(number);
        fractional=(-integral)-number;
    }
    else
    {
        integral = (int)number;
        fractional=number - integral;
    }

    fractional+=0.005;
    fractional*=100.0;

    getDigits(integral);

    for (int i=0 ; i<vec.size() ; i+=3)
        hundredToWords(i);
    WIntegral=words;

    vec.clear();
    words.clear();
    getDigits(fractional);
   for (int i=0 ; i<vec.size() ; i+=3)
       hundredToWords(i);
   WFractional=words;
   if (WIntegral=="")
       WIntegral = "zero";
   if(WFractional=="")
       WFractional= "zero";

   return WIntegral + " zł "+WFractional+ " gr";

}
void NumberToWords :: getDigits(int number)
{
    do{

        vec.push_back(number%10);
        number=number/10;
    }while(number>0);
}

void NumberToWords::hundredToWords(int start)
{
    int i=start;
    int end;
    start+3<vec.size() ? end=start+3 : end=vec.size();
    QString hundred;
    if(vec.size()>start+1)
       {
         if(vec[start+1]==1)
         {vec[start+1]=10+vec[start];
             i=start+1;}
       }
    hundred.push_front(toWord(vec[i]));
    i++;
    for ( ;i<end;i++)
    {

        hundred.push_front(toWord(vec[i]*qPow(10,i%3)));
    }

    words.push_front(addNumeral(start));
    words.push_front(hundred);

}
int NumberToWords :: getVariant(int start)
{


    if(vec[start]==1 && start==vec.size()-1) return 1;
    else if(vec[start]>=2 && vec[start]<=4) return 2;
    else if (vec[start]>4) return 3;
    if (start+2<=vec.size())
    {
    if (vec[start+1] == 1 || vec[start]==1 || vec[start]==0)
     return 3;
    }
    return 2;
}
QString NumberToWords::addNumeral(int start)
{
    int variant=getVariant(start);

    if (start<3) return "";
    if (start>=3 && start <=5)
    {
        switch (variant)
        {
            case 1: return "tysiąc ";
            case 2: return "tysiace ";
            case 3: return "tysięcy ";

        }
    }
    if (start>=6 && start <=8)
    {
        switch (variant)
        {
            case 1: return "milion ";
            case 2: return "miliony ";
            case 3: return "milionów ";

        }
   }
   return "miliard ";

}
QString NumberToWords::toWord(int number)
{
    switch(number){
        case 1: return "jeden ";
        case 2: return "dwa ";
        case 3: return "trzy ";
        case 4: return "cztery ";
        case 5: return "pięć ";
        case 6: return "sześć ";
        case 7: return "siedem ";
        case 8: return "osiem ";
        case 9: return "dziewięć ";
        case 10: return "dziesięć ";
        case 11: return "jedenaście ";
        case 12: return "dwanaście ";
        case 13: return "trzynaście ";
        case 14: return "czternaście ";
        case 15: return "piętnaście ";
        case 16: return "szesnaście ";
        case 17: return "siedemnaście ";
        case 18: return "osiemnaście ";
        case 19: return "dziewiętnaście ";
        case 20: return "dwadzieścia ";
        case 30: return "trzydzieści ";
        case 40: return "czterdzieści ";
        case 50: return "pięćdziesiąt ";
        case 60: return "sześćdziesiąt ";
        case 70: return "siedemdziesiąt ";
        case 80: return "osiemdziesiąt ";
        case 90: return "dziewięćdziesiąt ";
        case 100: return "sto  ";
        case 200: return "dwieście ";
        case 300: return "trzysta ";
        case 400: return "czterysta ";
        case 500: return "pięćset ";
        case 600: return "sześćset ";
        case 700: return "siedemset ";
        case 800: return "osiemset ";
        case 900: return "dziewięćset ";
    }
    return "";
}

NumberToWords::~NumberToWords(){}
