#ifndef DOCUMENTSERVICE_H
#define DOCUMENTSERVICE_H

#include "Document/DocumentPositionService.h"
#include "Document/StoreResultService.h"
#include "Other/Service.h"

class DocumentService : public Service
{
private:
    DocumentModel *model;
protected:
    DocumentPositionService *documentPositionService;
    StoreResultService *storeResultService;
    RelatedDocumentModel *relatedDocumentModel;
public:
    DocumentService();
    ~DocumentService();

    QVector<DocumentPosition> getPositions(QString documentSymbol);
    void setStoreResult(bool storeResult);
};

#endif // DOCUMENTSERVICE_H
