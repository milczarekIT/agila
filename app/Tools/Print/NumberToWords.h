#ifndef NUMBERTOWORDS_H
#define NUMBERTOWORDS_H

#include <QString>
#include <QVector>
#include <qmath.h>

class NumberToWords
{
    QString toWord(int number);
    QVector <int>vec;
    QString words;
    void hundredToWords(int start);
    QString addNumeral (int power);
    int getVariant (int start);
    void getDigits(int number);
public:
    QString toWords(double number);
    NumberToWords();
    ~NumberToWords();
};

#endif // NUMBERTOWORDS_H
