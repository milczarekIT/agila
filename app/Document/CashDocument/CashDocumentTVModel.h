#ifndef CASHDOCUMENTTVMODEL_H
#define CASHDOCUMENTTVMODEL_H

#include "Document/DocumentModel.h"
#include "Contractor/ContractorModel.h"
#include "Document/DocumentTVDisplayer.h"
#include "Document/CashDocument/CashDocument.h"
#include "Document/DocumentTVModel.h"

class CashDocumentTVModel : public DocumentTVModel
{
    void initHeaders();
public:
    CashDocumentTVModel();
    ~CashDocumentTVModel();

    void getDocuments();
};

#endif // CASHDOCUMENTTVMODEL_H
