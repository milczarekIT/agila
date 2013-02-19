#ifndef DOCUMENTNUMERATORCONTROLLER_H
#define DOCUMENTNUMERATORCONTROLLER_H

#include <QString>
#include <QVector>
#include <QVariant>
#include <QDebug>
#include <QDate>
#include <QRegExp>
#include <QStringList>
#include "Document/SymbolSequence.h"
#include "Document/Symbol.h"
#include "Document/DocumentNumeratorModel.h"
#include "Document/DocumentInfoModel.h"

/**
  * Klasa odpowiedzialna za wyznaczenie kolejnego symbolu dokumentu
  * Zawiera jedną metodę publiczną: getNextSymbol();
  *
  * @example DocumentNumeratorController *dnc = new DocumentNumeratorController()
  *          QString nextSymbol = dnc->getNextSymbol("FV");
  *          delete dnc;
  *
  * @see getNextSymbol(QString documentType);
  *
  */
class DocumentNumeratorController
{
private:
    QDate today;

    /**
      * Wektor dozwolonych znaków/sekwencji w formacie numerowania np. MM, YYYY, / etc.
      */
    QVector<QString> allowedSequence;

    /**
      * sekwencje jakie wystąpiły w formacie numerowania. Oprócz sekwencji dozwolonych mogą być znaki użytkownika np. B
      */
    QVector<SymbolSequence> formatSequences;

    /**
      * Typ dokumentu np. FV, PZ, WZ etc.
      */
    QString documentType;

    /**
      * Poprzedni symbol dokumentu danego typu
      */
    QString previousSymbolStr;

    /**
      * Wskaźnik na obiekt przechowujący dane dot. poprzedniego numeru.
      * Obiekt przechowuje informacje np. o dniu, miesiącu, roku, co stanowi podstawę do wyznaczenia kolejnego nr dokumentu
      */
    Symbol *previousSymbol;

    /**
      * Format numerowania odczytany z bazy
      */
    QString numberingFormat;

    /**
      * Wzorzec (RegExp) dla formatu
      */
    QString formatPattern;

    /**
      * Inicjacja wektora zdefiniowanych sekwencji
      */
    void initAllowedSequences(QString documentType);

    /**
      * Porównanie, czy obecny format numerowania jest taki sam poprzednio
      */
    bool isSameFormat();

    /**
      * Odczytanie obecnego formatu numerowania
      */
    void initFormatSequences(QString numberingFormat);

    /**
      * Zwraca wzorzec dla wyrażenia regularnego w celu porównania obecnego formatu numerowania z poprzednim symbolem
      */
    QString getRexExpPattern();

    /**
      * Sprawdza i zapisuje jeśli w formacie numerowania wystąpiły znaki użytkownika tzn. z poza dozwolonych sekwencji
      * Np. w formacie "FV #/MM/YYYYB" znakiem użytkownika jest B
      */
    void readUserChars();

    /**
      * Odczytuje dane z poprzedniego symbolu. Odczytuje dane takie jak DD, MM, YYYY,
      * w celu wyznaczenia kolejnego poprawnego numeru
      */
    void readVariablesFromPrevious();

    /**
      * Metoda ostatecznie wyznaczająca następny symbol, na podstawie wcześniejszych metod, danych
      * @param sameFormat - jeśli format się nie zmienił, to wartość true, w przeciwnym wypadku false
      * @see isSameFormat()
      */
    QString prepareNextSymbol(bool sameFormat = true);

    /**
      * Metoda wyznaczająca następny nr. Decyduje czy numer ma być zwiększony o jeden do poprzedniego, czy nr = 1 (np. nowy rok)
      */
    int getNextNr();

    /**
      * Szuka ciągu/znaku substring w ciągu numbering. Jeśli znajdzie sekwencje to dodaje ją
      * (oraz położenie) do QVectora sequences. Szuka wielu wystąpień (w przeciwieństwie do QString::contains())
      */
    void searchSequence(QString numbering, QString substring);

    /**
      * Sortuje sekwencje znaków, które wystąpiły w formacie numerowania wg kolejności wystąpień
      * Sortowany jest wektor formatSequences.
      */
    void sortSequences();

    DocumentNumeratorModel *model;

public:
    DocumentNumeratorController(QString documentType);
    ~DocumentNumeratorController();

    /**
      * Wyznacza prawidłowy symbol dokumentu, zgodnie ze zdefiniowanym formatem
      * @param documentType - typ dokumentu np. "FV", "PZ", "WZ"
      * @return następny symbol dokumentu
      */
    QString getNextSymbol();

    /**
      * Sprawdza czy symbol (wprowadzony przez użytkownika) jest poprawny
      * @return true - poprawny
      *         false - niepoprawny
      */
    bool isValidSymbol(QString symbol);

    /**
      * Sprawdza czy symbol jest wolny
      */
    bool isAvailableSymbol(QString symbol);

};

#endif // DOCUMENTNUMERATORCONTROLLER_H
