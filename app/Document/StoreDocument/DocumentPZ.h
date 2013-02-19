#ifndef DOCUMENTPZ_H
#define DOCUMENTPZ_H

#include "Document/Document.h"

/**
  Klasa przechowująca wszystkie pola dokumentu przyjęcia zewnętrznego
  @author Daniel Wojda
  */


class DocumentPZ : public Document  {

private:

    QDate storeDate; // data przyjecia magazynowego
    SimpleStructure transport;  //rodzaj transportu jakim przybył towar

public:
    DocumentPZ();
    ~DocumentPZ();

    QDate getStoreDate();
    SimpleStructure getTransport();

    void setStoreDate(QDate storeDate);
    void setTransport(SimpleStructure transport);    
    int operator ==(DocumentPZ in);

};

#endif // PZDOCUMENT_H
