#ifndef DocumentZDController_H
#define DocumentZDController_H

#include "Document/OrderDocument/DocumentZDView.h"
#include "Document/OrderDocument/DocumentZKView.h"
#include "Document/SaleDocument/InvoiceController.h"
#include "Document/OrderDocument/OrderService.h"
#include "Document/OrderDocument/OrderManager.h"

class OrderManager;
class DocumentZDView;

class DocumentZDController : public InvoiceController  {
    Q_OBJECT

public:
    DocumentZDController(QWidget* parent, QString symbol, bool edit);
    void exec();
    void exec(QString Symbol);
    ~DocumentZDController();
    void addGood();
    bool isChangesOccured();
    void getOrderData();

private:
  void initManagerConnections();
  OrderManager* managerOrd;

public slots:

    void checkRequredFields();
    void checkChanges();
    };

#endif // DocumentZDController_H
