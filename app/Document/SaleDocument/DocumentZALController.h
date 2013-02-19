#ifndef DocumentZALCONTROLLER_H
#define DocumentZALCONTROLLER_H

#include "Document/SaleDocument/DocumentZALService.h"
#include "Document/SaleDocument/DocumentZALView.h"
#include "Document/SaleDocument/DocumentZALManager.h"
#include "Document/SaleDocument/SaleController.h"

class DocumentZALController :  public SaleController  {

    Q_OBJECT

public:

    DocumentZALController(QWidget* parent, QString symbol, bool edit);
    ~DocumentZALController();
    void exec();
    void exec(QString symbol);
    void insertOrderData(Order order);

private:

    DocumentZALService *zalService;
    MOPModel *mopModel;
    void fillBox(QComboBox *box,QVector<MethodOfPayment> values);
    bool isChangesOccured();
    void restoreTableState();
    void saveTableState();
    void setPreviousZAL(Document documentZAL);
    void addToTable();
    void insertZAL(int i,int id, QTableWidgetItem *text);
    bool isOtherZal(SimpleDocumentInfo simple);
    void setGoodsValue();

public slots:
    void getDocumentData();
    void printDoc();
    void selectZAL();
    void updatePaymentDate();
    void selectOrderOrFacture();
    void changedRealizedOrSymbol();
    void changedPaid();
    void removeZal();

};

#endif // DocumentZALCONTROLLER_H
