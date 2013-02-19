#ifndef PRICELISTCONTROLLER_H
#define PRICELISTCONTROLLER_H

#include "PriceListView.h"
#include "Document/PriceDocument/PriceListService.h"
#include "Document/PriceDocument/PriceDocumentController.h"
class PriceListView;

class PriceListController : public PriceDocumentController
{
    Q_OBJECT

private:
    PriceListService *service;
    QString getNextSymbol();

public:
    explicit PriceListController(QObject *parent = 0);
    ~PriceListController();
    PriceList getDataFromView();
    void add();
    void edit(QString symbol);

signals:
    
public slots:
    int exec(QString symbol);
    void initBasicData();
    
};

#endif // PRICELISTCONTROLLER_H
