#ifndef OrderController_H
#define OrderController_H

#include "Document/OrderDocument/OrderView.h"
#include "Document/SaleDocument/SaleController.h"
#include "Document/OrderDocument/OrderService.h"
#include "Document/OrderDocument/OrderManager.h"
#include "Tools/Print/PrintOrderDocumentController.h"

class OrderController : public SaleController  {

    Q_OBJECT

public:
    OrderController(QWidget* parent, QString symbol, bool edit);
    ~OrderController();

    void exec();
    void exec(QString Symbol);
    bool isChangesOccured();


private:
    OrderService* orderService;
    void restoreTableState();
    void saveTableState();

public slots:
    void getDocumentData();
    void printDoc();
    void changedRealizedOrSymbol();

        };

#endif // OrderController_H
