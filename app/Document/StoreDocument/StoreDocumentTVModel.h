#ifndef STOREDOCUMENTTVMODEL_H
#define STOREDOCUMENTTVMODEL_H

#include "Document/DocumentModel.h"
#include "Document/DocumentTVDisplayer.h"
#include "Contractor/ContractorService.h"
#include "Document/DocumentTVModel.h"

class StoreDocumentTVModel : public DocumentTVModel
{
    void initHeaders();

public:
    StoreDocumentTVModel();

    void getDocuments();

};

#endif // STOREDOCUMENTMODEL_H
