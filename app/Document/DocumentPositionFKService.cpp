#include "DocumentPositionFKService.h"

DocumentPositionFKService::DocumentPositionFKService(StoreResultService *storeResultService) : DocumentPositionService(storeResultService)
{
    model = new DocumentPositionFKModel();
}

DocumentPositionFKService::~DocumentPositionFKService()
{
    delete model;
}

void DocumentPositionFKService::addPositions(QString documentSymbol, QVector<DocumentPosition> positionsFK, QVector<DocumentPosition> positionsInvoice) {

    this->positionsFK = positionsFK;
    this->positionsInvoice = positionsInvoice;

    for(int i = 0; i < positionsFK.size(); i++) {
       model->addPosition(documentSymbol, positionsFK[i]);

       if(storeResultService->isStoreResult())
           callDiffStoreResult(positionsFK[i]);
    }
}

void DocumentPositionFKService::callDiffStoreResult(DocumentPosition position) {

    DocumentPosition diffPosition;
    diffPosition = getDiffPosition(position);
    storeResultService->callStoreResult(diffPosition);
}

DocumentPosition DocumentPositionFKService::getDiffPosition(DocumentPosition position)
{
    DocumentPosition diffPosition;
    if(!this->positionsInvoice.contains(position))
    {
        indexAtInvoiceGoodsVector = this->searchPosition(position.getGood().getId(), this->positionsInvoice);
        if(isPositionAtInvoice())
        {
            float diffQuantity = position.getQuantity() - positionsInvoice[indexAtInvoiceGoodsVector].getQuantity();
            diffPosition = position;
            diffPosition.setQuantity(diffQuantity);

            return diffPosition; // pozycja z ilością: różnica fv-fk
        }
        else
            return position;
    }
    else
    {
        diffPosition = position;
        diffPosition.setQuantity(0); // nic sie nie zmieniło w stosunku do fv, diffQuantity = 0
        return diffPosition;
    }

}

bool DocumentPositionFKService::isPositionAtInvoice() {
    return (indexAtInvoiceGoodsVector != -1);
}


void DocumentPositionFKService::cancelDiffStoreResultForPositions(QVector<DocumentPosition> positionsFK, QVector<DocumentPosition> positionsInvoice) {

    this->positionsFK = positionsFK;
    this->positionsInvoice = positionsInvoice;

    DocumentPosition diffPosition;
    for(int i = 0; i < positionsFK.size(); i++)
    {
        diffPosition = getDiffPosition(positionsFK[i]); // diffPosition zawiera ilosc bedącą różnicą ilości fk-fv
        this->storeResultService->cancelStoreResult(diffPosition);
    }
}

/*void DocumentPositionFKService::updateDocumentPositionsFK(Document oldDocument, Document newDocument)
{
    QVector<DocumentPosition> oldPositions, newPositions;
    oldPositions = oldDocument.getDocumentPositions();
    newPositions = newDocument.getDocumentPositions();

    if(oldPositions != newPositions) // czy vectory pozycji zamówionych są różne
        this->editPositions(newDocument.getSymbol(), oldPositions, newPositions);
    else if(oldDocument.getStoreResult() != newDocument.getStoreResult()) // gdy w edycji tylko zmiana wywołania skutku magazynowego
        storeResultService->changeStoreResult(newPositions, newDocument.getStoreResult());
}*/
