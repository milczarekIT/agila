#ifndef DocumentWZ_H
#define DocumentWZ_H

#include "Document/Document.h"
#include "Contractor/Contractor.h"


/**
  Klasa przechowująca wszystkie pola dokumentu przyjęcia zewnętrznego
  @author Daniel Wojda
  */

class DocumentWZ : public Document  {

private:
    QString factureSymbol;
    QDate sendDate; // data wydania magazynowego
    SimpleStructure transport;  //rodzaj transportu jakim przybył towar
    QString waybillNumber; // nr listu przewozowego
    int shipping;

public:
    DocumentWZ();

    static const int SHIPPING_NOT_APLICABLE = 0; // nie dotyczy
    static const int SHIPPING_STORE = 1; // na koszt magazynu
    static const int SHIPPING_RECEIPMENT = 2; // na koszt odbiorcy

    QString getFactureSymbol();
    QDate getSendDate();
    SimpleStructure getTransport();
    QString getWaybillNumber();
    int getShipping();

    void setFactureSymbol(QString symbol);
    void setSendDate(QDate sendDate);
    void setTransport(SimpleStructure transport);
    void setWaybillNumber(QString waybillNumber);
    void setShipping(int shipping);
    int operator ==(DocumentWZ in);
};

#endif // WZDOCUMENT_H
