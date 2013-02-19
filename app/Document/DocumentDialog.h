#ifndef DOCUMENTDIALOG_H
#define DOCUMENTDIALOG_H

#include <QGridLayout>
#include <QLineEdit>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QTabWidget>
#include <QDateEdit>
#include "Components/TableView.h"
#include "Goods/GoodsTVModel.h"
#include "Goods/GoodsModel.h"

class DocumentDialog : public QDialog   {
    Q_OBJECT

protected:
    QGridLayout* mainLayout;

public:
    QDialogButtonBox* buttonBox;
    QPushButton* buttonChangeContractor;
    QPushButton* buttonGoodAdd;
    QPushButton* buttonGoodEdit;
    QPushButton* buttonGoodDel;

    //Dokument:
    QLabel* labelDocumentSymbol;
    QLabel* labelDocumentPlace;
    QLabel* labelIssueDate;      //data wystawienia dokumentu


    QLineEdit* lineDocumentSymbol;
    QLineEdit* lineDocumentPlace;
    QDateEdit* dateIssue;       //data wystawienia dokumentu

    //Kontrahent
    QLabel* labelName;
    QLabel* labelPostCode;
    QLabel* labelCity;
    QLabel* labelAddress;
    QLabel* labelTIN;
    QLabel* labelRegon;

    QLineEdit* lineName;
    QLineEdit* linePostCode;
    QLineEdit* lineCity;
    QLineEdit* lineAddress;
    QLineEdit* lineTIN;
    QLineEdit* lineRegon;

    //tabela towarów
    TableView* goodsTable;
    QStringList goodsHeaders;
    QLabel* labelGoodsValue;
    QLineEdit* lineGoodsValue;
    GoodsTVModel* goodsTVModel;
public:
    explicit DocumentDialog(QWidget *parent);

    //virtual void addAllComponents() = 0;
    void initLabels();
    void initLineEdits();
    void initButtons();
    void initGoodsTable();


signals:

public slots:

};

#endif // DOCUMENTDIALOG_H
