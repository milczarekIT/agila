#include "DocumentPositionService.h"

DocumentPositionService::DocumentPositionService(StoreResultService *storeResultService)
{
    model = new DocumentPositionModel();
    this->storeResultService = storeResultService;
}

DocumentPositionService::~DocumentPositionService() {
    delete model;
}

QVector<DocumentPosition> DocumentPositionService::getPositions(QString documentSymbol) {
    return model->getPositions(documentSymbol);
}

// osobna metoda dla FK, w przypadku zmian uwzględnić także DocumentPositionsFK::addPositions
void DocumentPositionService::addPositions(QString documentSymbol, QVector<DocumentPosition> positions)
{
    for(int i = 0; i < positions.size(); i++) {
        model->addPosition(documentSymbol, positions[i]);

        if(storeResultService->isStoreResult())
            storeResultService->callStoreResult(positions[i]);
    }
}

void DocumentPositionService::editPositions(QString documentSymbol, QVector<DocumentPosition> oldPositions, QVector<DocumentPosition> newPositions)
{
    for(int i = 0; i < newPositions.size(); i++)
    {
        if(!oldPositions.contains(newPositions[i]))
        {
            indexAtOldPosVector = searchPosition(newPositions[i].getGood().getId(), oldPositions);

            if(isGoodAtVectorWithOtherValues())
            {
                model->editPosition(documentSymbol, oldPositions[indexAtOldPosVector], newPositions[i]);

                if(storeResultService->isStoreResult())
                    storeResultService->callDiffStoreResult(oldPositions[indexAtOldPosVector], newPositions[i]);

                oldPositions[indexAtOldPosVector] = newPositions[i];
            }
            else
            {
                model->addPosition(documentSymbol, newPositions[i]);

                if(storeResultService->isStoreResult())
                    storeResultService->callStoreResult(newPositions[i]);

                oldPositions.append(newPositions[i]);
            }
        }
    }
    /*
     * jeśli dodano lub edytowano pozycje na fakturze to oldPositions i newPositions powinny być teraz takie same
     * jeśli nie są tzn., że w nowej fakturze usunięto pozycje ze starej faktury
     */
    if(oldPositions != newPositions)
    {
        for(int i = 0; i < oldPositions.size(); i++)
        {
            if(!newPositions.contains(oldPositions[i]))
            {
                model->removePosition(documentSymbol, oldPositions[i]);
                oldPositions.remove(i);

                if(storeResultService->isStoreResult())
                    storeResultService->cancelStoreResult(oldPositions[i]);
            }
        }
    }
}

bool DocumentPositionService::isGoodAtVectorWithOtherValues() {
    return indexAtOldPosVector != -1;
}

void DocumentPositionService::removePositions(QString documentSymbol) {
    try {
        model->removePositions(documentSymbol);
    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }
}

void DocumentPositionService::updateDocumentPositions(Document oldDocument, Document newDocument)
{
    QVector<DocumentPosition> oldPositions, newPositions;
    oldPositions = oldDocument.getDocumentPositions();
    newPositions = newDocument.getDocumentPositions();

    if(oldPositions != newPositions) // czy vectory pozycji zamówionych są różne
        this->editPositions(newDocument.getSymbol(), oldPositions, newPositions);
    else if(oldDocument.getStoreResult() != newDocument.getStoreResult()) // gdy w edycji tylko zmiana wywołania skutku magazynowego
        storeResultService->changeStoreResult(newPositions, newDocument.getStoreResult());
}

int DocumentPositionService::searchPosition(int idGood, QVector<DocumentPosition> vector)
{
    for(int i = 0; i < vector.size(); i++)
    {
        if(vector[i].getGood().getId() == idGood)
            return i;
    }
    return -1;
}

void DocumentPositionService::setStoreResult(bool storeResult) {
    storeResultService->setStoreResult(storeResult);
}
