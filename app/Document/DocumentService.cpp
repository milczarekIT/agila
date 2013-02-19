#include "DocumentService.h"

DocumentService::DocumentService()
{
    storeResultService = new StoreResultService();
    storeResultService->setDecreasedQuantity();
    storeResultService->setStoreResult(true);
    documentPositionService = new DocumentPositionService(storeResultService);

    relatedDocumentModel = new RelatedDocumentModel();
    model = new DocumentModel();
}

DocumentService::~DocumentService() {
    //delete storeResultService;
    delete documentPositionService;
    delete relatedDocumentModel;
    delete model;
}

QVector<DocumentPosition> DocumentService::getPositions(QString documentSymbol) {
    return documentPositionService->getPositions(documentSymbol);
}

void DocumentService::setStoreResult(bool storeResult){
    storeResultService->setStoreResult(storeResult);
}

