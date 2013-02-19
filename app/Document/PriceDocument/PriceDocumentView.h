#ifndef PRICEDOCUMENTVIEW_H
#define PRICEDOCUMENTVIEW_H

#include <QDate>
#include <QLabel>
#include <QDialog>
#include <QLineEdit>
#include <QGroupBox>
#include <QTextEdit>
#include <QComboBox>
#include <QTableWidget>
#include <QGridLayout>
#include <QRadioButton>
#include <QDialogButtonBox>
#include "Components/Button.h"
#include "Components/DateEdit.h"

class PriceDocumentView : public QDialog
{
    Q_OBJECT

protected:

    QGridLayout *layout;
    QGroupBox *mainInfos;
    QLineEdit *sign;
    DateEdit *createDate;
    DateEdit *dateFrom;
    DateEdit *dateTo;
    QRadioButton *notConcerns;
    QTableWidget *positions;
    Button *chooseGood;
    Button *deleteGood;
    QDialogButtonBox* buttonBox;
    QComboBox *priceLevel;

    void initTableHeaders();
    void initTableHeadersSize();

public:
    explicit PriceDocumentView(QWidget *parent = 0);

    void setMainWidgets();
    virtual void initWidgets();
    QDialogButtonBox *createButtonBox();
    void setDateLastDayOfMonth(DateEdit *dateEdit);

    QGroupBox *getMainInfos();
    QLineEdit *getSign();
    DateEdit *getCreateDate();
    DateEdit *getDateFrom();
    DateEdit *getDateTo();
    QRadioButton *getNotConcerns();
    QTableWidget *getPositions();
    Button *getChooseGood();
    Button *getDeleteGood();
    QDialogButtonBox* getButtonBox();
    QComboBox *getPriceLevel();

    virtual QString getSymbol();
    virtual QLineEdit *getName() = 0;
    virtual QTextEdit *getDescribe() = 0;
    virtual QTextEdit *getContractorData() = 0;
    virtual void initConnections() = 0;
    virtual void setGUISettings();
    virtual QGroupBox *setMainInfoWidgets() = 0;
    
signals:
    
public slots:
    
};

#endif // PRICEDOCUMENTVIEW_H
