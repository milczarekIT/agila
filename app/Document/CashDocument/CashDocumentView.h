#ifndef CASHDOCUMENTVIEW_H
#define CASHDOCUMENTVIEW_H

#include <QDialog>
#include "Components/ButtonBox.h"
#include "Components/Button.h"
#include "Components/DateEdit.h"
#include "Document/CashDocument/CashDocumentController.h"
class CashDocumentController;

class CashDocumentView : public QDialog
{
    Q_OBJECT

private:
    Button *buttonChangeContractor;
    Button *buttonSelectInvoice;
    Button *buttonPrint;
    QGridLayout *mainLayout;
    QTextEdit *contractorData;
    QTextEdit *textDescription;
    QLineEdit *lineSymbol;
    DateEdit *dateOfIssue;
    DateEdit *dateOfPayment;
    QLineEdit *lineAmountOfPayment;
    QLineEdit *lineTitle;
    QLineEdit *lineIssuedForDocument;
    QLineEdit *lineReceiveName;
    QLineEdit *lineIssueName;
    QLineEdit *lineDocumentPlace;
    ButtonBox* buttonBox;

    CashDocumentController *controller;
    void initInterface();
    void initConnections();
    void initLayout();
    void setDate(QDate saleDate);
    void setDateIssue(QDate issueDate);

public:
    explicit CashDocumentView(CashDocumentController *controller, QWidget *parent = 0);
    ~CashDocumentView();
    Button *getButtonChangeContractor();
    QTextEdit *getContractorData();
    QLineEdit *getLineSymbol();
    DateEdit *getDateOfIssue();
    DateEdit *getDateOfPayment();
    QLineEdit *getLineAmountOfPayment();
    QLineEdit *getLineTitle();
    QLineEdit *getLineIssuedForDocument();
    QLineEdit *getLineReceiveName();
    QLineEdit *getLineIssueName();
    QLineEdit *getLineDocumentPlace();
    QTextEdit *getTextDescription();
    ButtonBox* getButtonBox();
};

#endif // CASHDOCUMENTVIEW_H
