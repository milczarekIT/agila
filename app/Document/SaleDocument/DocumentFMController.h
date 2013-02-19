#ifndef DOCUMENTFMCONTROLLER_H
#define DOCUMENTFMCONTROLLER_H

#include "Document/SaleDocument/DocumentFMView.h"
#include "Document/SaleDocument/SaleController.h"
#include "Document/SaleDocument/DocumentFMManager.h"

class DocumentFMController : public SaleController  {

    Q_OBJECT

public:

    DocumentFMController(QWidget* parent,QString symbol, bool edit);
    ~DocumentFMController();

    void exec();
    void exec(QString Symbol);
    void insertOrderData(Order order);

private:

    InvoiceService *invoiceService;
    MOPModel *mopModel;
    void fillBox(QComboBox *box,QVector<MethodOfPayment> values);

    bool isChangesOccured();
    void selectGoods();
    void addGood();
    void setGoodsValue();
    bool isQuantityColumn(int column);
    void restoreTableState();
    void saveTableState();

public slots:
    void getDocumentData();
    void printDoc() ;
    void updatePaymentDate();
    void selectOrderOrFacture();
    void changedPaid();

    };

#endif // DOCUMENTFMCONTROLLER_H

