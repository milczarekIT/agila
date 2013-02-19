#ifndef PRICELISTVIEW_H
#define PRICELISTVIEW_H

#include "PriceListController.h"
#include "Document/PriceDocument/PriceDocumentView.h"
class PriceListController;

class PriceListView : public PriceDocumentView
{
    Q_OBJECT

private:
    PriceListController *controller;
    QLineEdit *name;
    QTextEdit *describe;

public:
    explicit PriceListView(PriceListController *controller, QWidget *parent = 0);
    void initConnections();
    void setGUISettings();
    void initWidgets();
    QGroupBox *setMainInfoWidgets();

    //akcesory
    QLineEdit *getName();
    QTextEdit *getDescribe();
    QTextEdit *getContractorData();
    QString getSymbol();
    
signals:
    
public slots:
    
};

#endif // PRICELISTVIEW_H
