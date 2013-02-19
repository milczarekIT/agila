#ifndef SYMBOLSEQUENCE_H
#define SYMBOLSEQUENCE_H

#include <QString>

/**
  * Klasa odpowiedzialna za przechowywanie sekwencji jakie wystąpiły w (formacie) symbolu dokumentu
  * Oprócz sekwencji przechowywane jest położenie jej wystąpienia
  * Przykładowe sekwencje: "/", "DD", "YYYY", " "
  * @see Controller/DocumentNumeratorController
  */
class SymbolSequence
{
    QString sequence;
    int index;
public:
    SymbolSequence();
    SymbolSequence(QString sequence, int index);

    void setSequence(QString sequence);
    void setIndex(int index);

    QString getSequence();
    int getIndex();
};

#endif // SYMBOLSEQUENCE_H
