#ifndef DOCUMENTPOSITIONFKSERVICE_H
#define DOCUMENTPOSITIONFKSERVICE_H

#include "Document/DocumentPositionFKModel.h"
#include "Document/StoreResultService.h"

class DocumentPositionFKService : public DocumentPositionService
{
    DocumentPositionFKModel *model;

    QVector<DocumentPosition> positionsFK;
    QVector<DocumentPosition> positionsInvoice;

    int indexAtInvoiceGoodsVector;

    void callDiffStoreResult(DocumentPosition position);
    DocumentPosition getDiffPosition(DocumentPosition position);
    bool isPositionAtInvoice();
public:
    DocumentPositionFKService(StoreResultService *storeResultService);
    ~DocumentPositionFKService();

    void addPositions(QString documentSymbol, QVector<DocumentPosition> positionsFK, QVector<DocumentPosition> positionsInvoice);
    void cancelDiffStoreResultForPositions(QVector<DocumentPosition> positionsFK, QVector<DocumentPosition> positionsInvoice);
};

#endif // DOCUMENTPOSITIONFKSERVICE_H
