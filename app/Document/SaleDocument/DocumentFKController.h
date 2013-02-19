#ifndef DOCUMENTFKCONTROLLER_H
#define DOCUMENTFKCONTROLLER_H

#include "Document/SaleDocument/DocumentFKView.h"
#include "SelectionWindows/SelectContractorController.h"
#include <QTableWidgetItem>
#include "Settings/SettingsModel.h"
#include "Document/DocumentPosition.h"
#include "Document/SaleDocument/DocumentFK.h"
#include "Document/SaleDocument/InvoiceService.h"
#include "Document/SaleDocument/DocumentFKService.h"
#include "Document/MethodOfPayment.h"
#include "Document/DocumentNumeratorController.h"
#include "SelectionWindows/SelectInvoiceController.h"
#include "Tools/Print/PrintSaleDocumentController.h"
#include "Document/DocumentValidator.h"
#include "Document/SaleDocument/DocumentFKManager.h"

class DocumentFKView;
class DocumentValidator;
class DocumentFKManager;

class DocumentFKController : public QObject  {

    Q_OBJECT

protected:

    DocumentFKView* view;
    DocumentFKManager *managerFK;
    TableStateManager *tableStateManager;
    DocumentValidator* validator;
    QString symbol;

    InvoiceService *invoiceService;
    DocumentFKService * fkService;
    SettingsModel *smodel;
    MOPModel *mopModel;
    DocumentNumeratorController *dnc;
    bool edition;
    bool first;
    bool totalFromBase;

    void fillBox(QComboBox *box,QVector<MethodOfPayment> values);
    virtual void getDocumentData();
    bool isQuantityColumn(int column);
    virtual void restoreTableState();
    virtual void saveTableState();

public:
    DocumentFKController(QWidget* parent, bool edit);
    ~DocumentFKController();
     DocumentFKController();
    virtual void exec();
    virtual void exec(QString symbol);

    bool isChangesOccured();
    DocumentFKView *getView();
    bool getEdition();
    DocumentFKManager* getManager();
    bool getFirst();
    QString getSymbol();
    void setFirst(bool first);
    void setGoodsValue();
    void insertGood(int i, int id, QTableWidgetItem *text);
    void addGood();
    virtual void insertInvoiceData(Document invoice);

public slots:

    void checkChanges();
    void updatePaymentDate();
    void checkRequredFields();
    void printDoc();
    void editGood(int row, int column);
    void removeGood();
    void selectContractor();
    virtual void selectInvoice();
    void selectGoods();
    void discountChanged();
    };


#endif // DOCUMENTFKCONTROLLER_H
