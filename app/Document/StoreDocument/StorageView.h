#ifndef StorageView_H
#define StorageView_H

/**
  @author Daniel Wojda
  */

#include "Document/StoreDocument/StorageController.h"
#include "Document/StoreDocument/StoreDocumentView.h"
class StorageController;

class StorageView : public StoreDocumentView {

public:
    StorageView(QWidget *parent, StorageController* controller);
    ~StorageView();
    void setTabOrders();

};

#endif // StorageView_H
