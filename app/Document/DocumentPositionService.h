#ifndef DOCUMENTPOSITIONSERVICE_H
#define DOCUMENTPOSITIONSERVICE_H

#include "Database/Database.h"
#include "Other/Service.h"
#include "Document/DocumentPositionModel.h"
#include "Document/StoreResultService.h"
class DocumentPositionModel;

class DocumentPositionService : public Service
{
    DocumentPositionModel *model;

    int indexAtOldPosVector;

    bool isGoodAtVectorWithOtherValues();
protected:
    StoreResultService *storeResultService;
public:
    DocumentPositionService(StoreResultService *storeResultService);
    ~DocumentPositionService();

    QVector<DocumentPosition> getPositions(QString documentSymbol);
    void addPositions(QString documentSymbol, QVector<DocumentPosition> positions);
    void editPositions(QString documentSymbol, QVector<DocumentPosition> oldPostions, QVector<DocumentPosition> newPostions);
    void updateDocumentPositions(Document oldDocument, Document newDocument); // Edycja pozycji i/lub zmiana skutku mag.
    void removePositions(QString documentSymbol);

    int searchPosition(int idGood, QVector<DocumentPosition> vector);

    void setStoreResult(bool storeResult);
};

#endif // DOCUMENTPOSITIONSERVICE_H
