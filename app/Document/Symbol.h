#ifndef SYMBOL_H
#define SYMBOL_H

/**
  * Przechowuje zmienne symbolu dokumentu.
  * @see Controller/DocumentNumeratorController
  */
class Symbol
{
    int nr;
    int dd;
    int mm;
    int yyyy;
public:
    Symbol();

    void setNr(int nr);
    void setDay(int dd);
    void setMonth(int mm);
    void setYear(int yyyy);

    int getNr();
    int getDay();
    int getMonth();
    int getYear();
};

#endif // SYMBOL_H
