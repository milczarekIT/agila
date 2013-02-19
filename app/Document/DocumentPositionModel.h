#ifndef DOCUMENTPOSITIONMODEL_H
#define DOCUMENTPOSITIONMODEL_H

#include "Database/Model.h"
#include "Goods/GoodsModel.h"
#include "Document/Document.h"
#include "Document/StoreResultService.h"
class StoreResultService;

/**
  * @author Bartosz Milczarek
  */
class DocumentPositionModel : public Model
{
    int warehouseId;
public:
    DocumentPositionModel();

    QVector<DocumentPosition> getPositions(QString documentSymbol);
    void addPosition(QString documentSymbol, DocumentPosition position);
    void editPosition(QString documentSymbol, DocumentPosition oldPosition, DocumentPosition newPosition);
    void removePosition(QString documentSymbol, DocumentPosition position);

    void removePositions(QString documentSymbol);

};

#endif // DOCUMENTPOSITIONMODEL_H
