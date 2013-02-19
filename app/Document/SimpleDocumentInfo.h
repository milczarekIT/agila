#ifndef SIMPLEDOCUMENTINFO_H
#define SIMPLEDOCUMENTINFO_H

#include <QString>
#include <QDate>
#include <QVariant>

/**
  * Klasa przechowująca podstawowe dane o dokumencie
  * Użycie: Obiekty tej klasy przechowywane w wektorze jako informacja nt. dokumentów powiązanych
  * @author Bartosz Milczarek
  */
class SimpleDocumentInfo
{
    QString type;
    QString symbol;
    QDate documentDate;
    double total;
public:
    SimpleDocumentInfo();

    void setType(QString type);
    void setSymbol(QString symbol);
    void setDocumentDate(QDate issueDate);
    void setTotal(double total);

    QString getType();
    QString getSymbol();
    QDate getDocumentDate();
    double getTotal();

    bool operator==(SimpleDocumentInfo sdi);
    QString toString();
};

#endif // SIMPLEDOCUMENTINFO_H
