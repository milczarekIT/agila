#ifndef DOCUMENTMODEL_H
#define DOCUMENTMODEL_H

#include "Database/Model.h"
#include "Goods/GoodsModel.h"
#include "Document/Document.h"
#include "Document/DocumentPosition.h"
#include "Document/DocumentPositionService.h"
#include "Document/StoreResultService.h"
#include "Settings/SettingsModel.h"
#include "Contractor/ContractorService.h"
#include "Document/PeopleModel.h"
#include "Document/DocumentPlaceModel.h"
#include "Document/RelatedDocumentModel.h"
class StoreResultService;
class DocumentPositionService;

/**
  * Wspólny model dla dokumentów sprzedaży i dokumentów magazynowych
  * Należy zwrócić uwagę na <code>storeResult</code> (czy wywołać skutek magazynowy) oraz
  * <code>increasedQuantity</code> (czy stan na magazynie dla tego dokumentu ma sie zmniejszać czy zwiększać
  */
class DocumentModel : public Model
{
protected:
    PeopleModel *peopleModel;
    DocumentPlaceModel *documentPlaceModel;
    Warehouse *currentWarehouse;

public:
    DocumentModel();
    ~DocumentModel();

    /**
      * Wstawia symbol wystawionego dokumentu jako ostatni symbol
      */
    void setLastDocumentSymbol(QString documentType, QString symbol);

};

#endif // DOCUMENTMODEL_H
