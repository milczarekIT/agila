#ifndef OFFERVIEW_H
#define OFFERVIEW_H

#include "Document/PriceDocument/OfferController.h"
#include "Document/PriceDocument/PriceDocumentView.h"
class OfferController;

class OfferView  : public PriceDocumentView
{
    Q_OBJECT

private:
    OfferController *controller;
    QTextEdit *contractorData;
    Button *selectContractor;

public:
    explicit OfferView(OfferController *controller, QWidget *parent = 0);
    void initConnections();
    void setGUISettings();
    void initWidgets();
    QGroupBox *setMainInfoWidgets();
    void setMainWidgets();

    //akcesory
    QLineEdit *getName();
    QTextEdit *getDescribe();
    QTextEdit *getContractorData();
    QString getSymbol();
    
signals:
    
public slots:
    
};

#endif // OFFERVIEW_H
