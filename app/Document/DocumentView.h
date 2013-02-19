#ifndef DOCUMENTVIEW_H
#define DOCUMENTVIEW_H

#include <QTableWidgetItem>
#include <QTextEdit>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>
#include <QGridLayout>
#include <QLineEdit>
#include <QDialog>
#include <QLabel>
#include "Contractor/Contractor.h"
#include "Components/DateEdit.h"
#include "Document/DocumentController.h"
#include "Components/ButtonBox.h"
#include "Components/Button.h"
class DocumentController;

class DocumentView : public QDialog
{
    Q_OBJECT

protected:

    virtual void initGoodsTable() = 0;
    virtual void initOptionalLineEdits() = 0;
    virtual void initOptionalButtons() = 0;
    virtual void initOptionalConnections() = 0;
    virtual void addOptionalComponents() = 0;
    virtual void setTabOrders();
    void initAlwaysUsedLineEdits();
    void initButtons();
    void initAlwaysUsedConnections();
    void addAlwaysUsedComponents();
    void setHeaders(int id, QTableWidgetItem *header);

    void closeEvent(QCloseEvent *event);

    QLineEdit *lineReceiveName;
    QLineEdit *lineDocumentSymbol;
    QLineEdit *lineDocumentPlace;
    QLineEdit *lineGoodsValue;
    QLabel * labelGoodsValue;
    QLineEdit *lineIssueName;
    Button* buttonChangeContractor;
    Button* buttonGoodAdd;
    Button* buttonGoodDel;
    Button* buttonOrderOrFactureAdd; //order w sprzedazy/zakupie lub faktura w magazynie

    QTextEdit *contractorData;
    QTableWidget *goodsTable;
    ButtonBox* buttonBox;
    QGridLayout* mainLayout;
    DateEdit *dateIssue;
    DocumentController* controller;

public:
    explicit DocumentView(QWidget* parent);
    ~DocumentView();

    virtual bool isPaid();
    virtual bool isStoreUpdating() = 0;
    virtual void setLineGoodsValueNet(double valueNet) = 0;
    virtual void setLineDiscount(double discount);
    void setLineDocumentSymbol(QString documentSymbol);
    void setLineDocumentPlace(QString documentPlace);
    void setLineGoodsValue(double goodsValue);
    virtual void setLineGoodsValueDiscount(double goodsValueWithDiscount);
    virtual void setAdvance(double advance);
    void setLineIssueName(QString issueName);
    void setLineReceiveName (QString receiveName);
    virtual void setSaleOrStoreDate(QDate date);
    void setDateIssue(QDate issueDate);
    virtual void setPaymentDate(QDate paymentDate);//data wystawienia dokumentu
    virtual void setCheckPaid(bool paid);
    virtual void setCheckStoreUpdate(bool update) = 0;
    void setContractorData(Contractor contractor);
    virtual void setRealized(bool realized);
    virtual void setRealizationDate(QDate realizationDate);

    virtual bool isRealized();
    virtual QDate getRealizationDate();
    QTextEdit *getContractorData();
    virtual QLineEdit* getDiscountOrWaybillNo();
    virtual QLineEdit* getPurchaseOrFactureSymbol();
    virtual QLineEdit *getLineOrderSymbol();
    QLineEdit *getLineDocumentSymbol();
    QLineEdit *getLineDocumentPlace();
    double getLineGoodsValue();
    virtual double getLineAdvance();
    virtual double getLineGoodsValueDiscount();
    virtual double getLineGoodsValueNet() = 0;
    QString getLineIssueName();
    QString getLineReceiveName ();
    virtual QDate getSaleOrStoreDate(); //Jako saleDate(data sprzedaży) oraz storeDate(data dostarczenia,wydania(PZ,WZ))
    QDate getDateIssue();
    virtual DateEdit* getPaymentDate();
    virtual QComboBox *getWayToPay(); //sposób płatności(dokumenty), lub kto obciążony kosztami(magazyn)
    virtual QComboBox *getComboBox();
    QTableWidget*getGoodsTable();
    virtual QTableWidget*getZALTable();
    DocumentController* getController();   

};

#endif // DOCUMENTVIEW_H
