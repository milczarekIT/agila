#include "StoreResultService.h"

StoreResultService::StoreResultService()
{
}

void StoreResultService::callStoreResult(QVector<DocumentPosition> positions)
{
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
    {
        for(int i = 0; i < positions.size(); i++)
            this->callStoreResult(positions[i]);
    }
}

void StoreResultService::callStoreResult(DocumentPosition position)
{
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
    {
        GoodsModel *gModel = new GoodsModel();
        GoodsCacheService *cacheService = new GoodsCacheService();

        int actualId = cacheService->getActualIdForId(position.getGood().getId());
        delete cacheService;

        if(this->isIncreasedQuantity())
            gModel->increaseQuantity(actualId, position.getQuantity());
        else
            gModel->decreaseQuantity(actualId, position.getQuantity());

        delete gModel;
    }
}

void StoreResultService::callDiffStoreResult(DocumentPosition oldPosition, DocumentPosition newPosition)
{
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
    {
        GoodsModel *gModel = new GoodsModel();
        float diffQuantity = newPosition.getQuantity() - oldPosition.getQuantity();

        GoodsCacheService *cacheService = new GoodsCacheService();
        int actualId = cacheService->getActualIdForId(newPosition.getGood().getId());
        delete cacheService;

        if(this->isIncreasedQuantity())
            gModel->increaseQuantity(actualId, diffQuantity);
        else
            gModel->decreaseQuantity(actualId, diffQuantity);

        delete gModel;
    }
}

void StoreResultService::cancelStoreResult(QVector<DocumentPosition> positions)
{
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
    {
        for(int i = 0; i < positions.size(); i++)
            this->cancelStoreResult(positions[i]);
    }
}

void StoreResultService::cancelStoreResult(DocumentPosition position)
{
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
    {
        GoodsModel *gModel = new GoodsModel();

        GoodsCacheService *cacheService = new GoodsCacheService();
        int actualId = cacheService->getActualIdForId(position.getGood().getId());
        delete cacheService;

        if(this->isIncreasedQuantity())
            gModel->decreaseQuantity(actualId, position.getQuantity());
        else
            gModel->increaseQuantity(actualId, position.getQuantity());

        delete gModel;
    }
}

void StoreResultService::changeStoreResult(QVector<DocumentPosition> positions, bool storeResult)
{
    if(storeResult == true)
        callStoreResult(positions);
    else
        cancelStoreResult(positions);
}

void StoreResultService::setStoreResult(bool storeResult) {
    this->storeResult = storeResult;
}

void StoreResultService::setIncreasedQuantity() {
    this->increasedQuantity = true;
}

void StoreResultService::setDecreasedQuantity() {
    this->increasedQuantity = false;
}

bool StoreResultService::isStoreResult() {
    return storeResult;
}

bool StoreResultService::isIncreasedQuantity() {
    return increasedQuantity;
}
