#ifndef OFFERCONTROLLER_H
#define OFFERCONTROLLER_H

#include "Document/PriceDocument/OfferView.h"
#include "Document/PriceDocument/OfferService.h"
#include "SelectionWindows/SelectContractorController.h"
#include "Document/PriceDocument/PriceDocumentController.h"
class OfferView;

class OfferController : public PriceDocumentController
{
    Q_OBJECT
    
private:
    OfferService *service;
    Contractor c;
    QString getNextSymbol();

public:
    explicit OfferController(QObject *parent = 0);
    ~OfferController();
    PriceList getDataFromView();
    void add();
    void edit(QString symbol);

signals:

public slots:
    int exec(QString symbol);
    void selectContractor();
};

#endif // OFFERCONTROLLER_H
