#ifndef PURCHASEDOCUMENTTVMODEL_H
#define PURCHASEDOCUMENTTVMODEL_H

#include "Document/DocumentModel.h"
#include "Document/DocumentTVDisplayer.h"
#include "Document/DocumentTVModel.h"

class PurchaseDocumentTVModel : public DocumentTVModel
{
    void initHeaders();

public:
    PurchaseDocumentTVModel();
    ~PurchaseDocumentTVModel();

    void getDocuments();
};

#endif // PURCHASEDOCUMENTTVMODEL_H
