#ifndef DOCUMENTPZVIEW_H
#define DOCUMENTPZVIEW_H

/**
  @author Daniel Wojda
  */

#include "Document/StoreDocument/DocumentPZController.h"
#include "Document/StoreDocument/StoreDocumentView.h"

class DocumentPZController;

class DocumentPZView : public StoreDocumentView {

public:
    DocumentPZView(QWidget *parent, DocumentPZController* controller);
    ~DocumentPZView();

    void setSaleOrStoreDate(QDate storeDate);
    QDate getSaleOrStoreDate();
    QComboBox *getComboBox();
    void initOptionalButtons();
    void initOptionalConnections();
    void setTabOrders();

private:
    void addPZComponents();
    void initPZComponents();
    DateEdit* storeDate;
    QComboBox* comboBoxTransport;

};

#endif // DOCUMENTPZVIEW_H
