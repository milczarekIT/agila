#ifndef DOCUMENTNKVIEW_H
#define DOCUMENTNKVIEW_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include "Document/PurchaseDocument/DocumentNKController.h"
#include "Components/DateEdit.h"
#include "Components/ButtonBox.h"
#include "Components/Button.h"
class DocumentNKController;

class DocumentNKView :  public QDialog  {
    Q_OBJECT

    DocumentNKController *controller;
    QWidget *parent;
    QGridLayout *mainLayout;

    // labels
    QLabel *labelDocumentSymbol;
    QLabel *labelDocumentPlace;
    QLabel *labelDocumentDate;
    QLabel *labelRelatedTo;
    QLabel *labelInvoiceDate;
    QLabel *labelReceiver;
    QLabel *labelCorrectedContents;
    QLabel *labelCorrectContents;
    QLabel *labelReceiveName;
    QLabel *labelIssueName;

    // lineEdits
    QLineEdit *lineDocumentSymbol;
    QLineEdit *lineDocumentPlace;
    QLineEdit *lineRelatedTo;
    QLineEdit *lineReceiveName;
    QLineEdit *lineIssueName;

    // textEdits
    QTextEdit *textReceiver;
    QTextEdit *textCorrected;
    QTextEdit *textCorrect;

    // buttons
    Button *buttonSelectReceiver;
    Button *buttonSelectInvoice;

    // dateEdits
    DateEdit *dateEditDocumentDate;
    DateEdit *dateEditInvoiceDate;

    ButtonBox* buttonBox;

    QFrame *line;

    void initLabels();
    void initLineEdits(); // lineEdit + textEdit
    void initDateEdits();
    void initButtons();
    void initConnections();
    void addAllComponents();
public:
    DocumentNKView(QWidget *parent, DocumentNKController* controller);
    ~DocumentNKView();

    void setReceiver(Contractor receiver);


    QLineEdit *getLineDocumentSymbol();
    QLineEdit *getLineDocumentPlace();
    QLineEdit *getLineRelatedTo();
    QLineEdit *getLineIssueName();
    QLineEdit *getLineReceiveName();
    QTextEdit *getTextReceiver();
    QTextEdit *getTextCorrected();
    QTextEdit *getTextCorrect();
    DateEdit *getDateEditDocumentDate();
    DateEdit *getDateEditInvoiceDate();
};

#endif // DOCUMENTNKVIEW_H
