#ifndef CASHDOCUMENTCONTROLLER_H
#define CASHDOCUMENTCONTROLLER_H

#include <QWidget>
#include "Contractor/Contractor.h"
#include "SelectionWindows/SelectContractorController.h"
#include "Document/CashDocument/CashDocumentView.h"
#include "SelectionWindows/SelectInvoiceController.h"
#include "Document/CashDocument/CashDocument.h"
#include "Document/CashDocument/CashDocumentValidator.h"
#include "Document/CashDocument/CashDocumentService.h"
#include "Document/DocumentNumeratorController.h"
#include "Settings/OtherSettings/SettingsOwnerController.h"
#include "Tools/Print/PrintManager.h"
class CashDocumentView;
class CashDocumentValidator;

class CashDocumentController : public QWidget
{
    Q_OBJECT

private:
    CashDocumentService *service;
    CashDocumentView *view;
    CashDocument document;
    CashDocument oldDocument;
    DocumentNumeratorController *dnc;
    CashDocumentValidator *validator;
    Contractor c;
    QString symbol;
    bool edition;    
    void setReceiveName(Contractor receiver);
    void setIssueName(Contractor issuer);
    void setReceiveName(QString name);
    void setIssueName(QString name);
    Contractor getMyData();
    bool isEmptyForm();

public:
    explicit CashDocumentController(QString symbol, bool edit, QWidget *parent);
    ~CashDocumentController();
    CashDocumentView *getView();
    CashDocument getCashDocument();
    void insertInvoiceData(Document invoice);
    void initData();

public slots:
    void selectContractor();
    void selectInvoice();
    Contractor getContractor();
    void exec(QString symbol);
    void exec();
    void print();
    void checkChanges();
    void checkRequiredFields();
    QString getSymbol();
};

#endif // CASHDOCUMENTCONTROLLER_H
