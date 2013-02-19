#ifndef DOCUMENTWZVIEW_H
#define DOCUMENTWZVIEW_H

/**
  @author Daniel Wojda
  */

#include "Document/StoreDocument/DocumentWZController.h"
#include "Document/StoreDocument/StoreDocumentView.h"

class DocumentWZController;

class DocumentWZView : public StoreDocumentView {


public:
    DocumentWZView(QWidget *parent, DocumentWZController* controller);
    ~DocumentWZView();
    void addWZComponents();
    void initWZComponents();
    void initOptionalButtons();
    void initOptionalConnections();
    QComboBox *getWayToPay();
    QLineEdit* getDiscountOrWaybillNo();
    QLineEdit *getPurchaseOrFactureSymbol();
    QDate getSaleOrStoreDate();
    void setSaleOrStoreDate(QDate storeDate);
    QComboBox *getComboBox();
    void setTabOrders();


private:

    QComboBox* comboPayForDelivery;
    QDateEdit* dateDelivery; //data wysałania towaru
    QLineEdit* lineNoCarraigeNote;   //numer listu przewozowego
    QLineEdit* lineNoFactureVat;
    QComboBox* comboBoxTransport;

};

#endif // DOCUMENTPZVIEW_H
