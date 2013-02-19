#ifndef DOCUMENTFKVIEW_H
#define DOCUMENTFKVIEW_H

#include <QDialog>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QTabWidget>
#include <QTableWidget>
#include <QCheckBox>

#include "Document/SaleDocument/DocumentFKController.h"
#include "SelectionWindows/SelectGoodController.h"
#include "Document/DocumentNumeratorController.h"
#include "Contractor/Contractor.h"
#include "Goods/Goods.h"
#include "Components/TableView.h"
#include "Goods/GoodsModel.h"
#include "Settings/SettingsModel.h"
#include "Components/DateEdit.h"
#include "Components/ButtonBox.h"
#include "Components/Button.h"

class DocumentFKController;

class DocumentFKView : public QDialog  {
   Q_OBJECT


public:
    DocumentFKView(QWidget *parent, DocumentFKController* controller);
    ~DocumentFKView();
    DocumentFKView(QWidget * parent );
    bool isPaid();
    bool isStoreUpdating();
    void setContractorDataOld(Contractor receiver);
    void setContractorDataNew(Contractor receiver);

    void setLineGoodsValueNetNew(double valueNetNew);
    void setLineGoodsValueNew(double goodsValueNew);
    void setLineGoodsValueDiscountNew(double goodsValueWithDiscountNew);

    void setLineToPayAfterCorrection(double toPay);
    void setLineGoodsValueNet(double valueNet);
    void setLineDiscount(double discount);
    void setLineDiscountNew(double discountNew);
    void setPurchaseDocSymbol(QString symbol);
    void setLineDocumentSymbol(QString documentSymbol);
    void setLineDocumentPlace(QString documentPlace);
    void setLineGoodsValue(double goodsValue);
    void setLineGoodsValueDiscount(double goodsValueWithDiscount);
    void setLineIssueName(QString issueName);
    void setLineReceiveName (QString receiveName);
    void setSaleDate(QDate saleDate);
    void setRealatedTo(QString realtedTo);
    void setDateEditInvoiceDate(QDate dateEditInvoiceDate);
    void setDateIssue(QDate issueDate);
    void setPaymentDate(QDate paymentDate);//data wystawienia dokumentu
    void setCheckPaid(bool paid);
    void setCheckStoreUpdate(bool update);
    QLineEdit *getPurchaseDocSymbol();
    QLineEdit *getLineDiscountNew();
    QLineEdit *getLineDiscount();
    QLineEdit *getLineDocumentSymbol();
    QLineEdit *getLineDocumentPlace();
    double getLineGoodsValue();
    double getLineGoodsValueNew();
    double getLineToPayAfterCorrection();
    double getLineGoodsValueNetNew();
    QString getLineIssueName();
    QString getLineReceiveName ();
    QDate getSaleDate();
    QDate getDateIssue();
    QDate getPaymentDate();//data wystawienia dokumentu
    QComboBox *getBoxWayToPay();
    QTableWidget*getGoodsTableOld();
    QTableWidget *getGoodsTableNew();
    QTextEdit *getContractorDataOld();
    QTextEdit *getContractorDataNew();
    QLineEdit * getLineRelatedTo();
    DateEdit *paymentDate;
    DocumentFKController* getController();

    virtual void closeEvent(QCloseEvent *event);
    void initLineEdits();
    void initButtons();
    void initGoodsTable();
    void initConnections();
    void addAllComponents();
    void initTabs();
    void setHeaders(int id, QTableWidgetItem *header);
    virtual void addAdditionalComopnent();

protected:

    QTabWidget * tabWidget;
    QTabWidget * tabBeforeCorrection;
    QTabWidget * tabAfterCorrection;
    QLineEdit * lineRelatedTo;
    DateEdit *dateEditInvoiceDate;
    //info o dokumencie:
    QLineEdit *lineDocumentSymbol;
    QLineEdit *lineDocumentPlace;
    DateEdit *dateIssue;
    Button *buttonSelectInvoice;

//info o dacie sprzedazy, dacie i sposobie zaplaty
    QLineEdit  *lineToPayAfterCorrection;
    QLineEdit *lineDiscount;
    QLineEdit *lineDiscountNew;
    DateEdit* saleDate;

 //combobox
    QComboBox* boxWayToPay;
    QCheckBox* checkPaid;
    QCheckBox* checkStoreUpdating;

    //tabela towarów
    QTableWidget *goodsTableOld;
    QLineEdit *lineGoodsValue;
    QLineEdit *lineGoodsValueDiscount;
    QLineEdit *lineGoodsValueNet;
    QLineEdit *linePurchaseDocSymbol;

    QTableWidget *goodsTableNew;
    QLineEdit *lineGoodsValueNew;
    QLineEdit *lineGoodsValueDiscountNew;
    QLineEdit *lineGoodsValueNetNew;

    //inne
    QLineEdit *lineReceiveName;
    QLineEdit *lineIssueName;

    QTextEdit *contractorDataOld;
    QTextEdit *contractorDataNew;

    DocumentFKController* controller;
    QGridLayout* mainLayout;
    QGridLayout* mainLayoutBeforeCorrection;
    QGridLayout* mainLayoutAfterCorrection;

    ButtonBox* buttonBox;
    Button* buttonChangeContractor;
    Button* buttonChangeGood;
    Button* buttonRemoveGood;

public slots :
   /**
   Slot publiczny odpowiedzialny za zmiane checkboxa zapłata w zaleznosci od daty zapłaty.
   (Jego funkcjonalosc sugeruje iz powinienen znajdowac sie w controllerze jednak tam odmawia on wspolpracy z nieznanych przyczyn.)
   */
   void changedDate();

};

#endif // DocumentFKView_H
