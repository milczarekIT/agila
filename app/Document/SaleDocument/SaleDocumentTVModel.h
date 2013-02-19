#ifndef SALEDOCUMENTTVMODEL_H
#define SALEDOCUMENTTVMODEL_H

#include "Document/DocumentModel.h"
#include "Document/DocumentTVDisplayer.h"
#include "Contractor/ContractorModel.h"
#include "Document/DocumentTVModel.h"

class SaleDocumentTVModel : public DocumentTVModel
{
    void initHeaders();

public:
    SaleDocumentTVModel();
    ~SaleDocumentTVModel();

    void getDocuments();

    void setDocTypeFilter(QString value);
    void setDocTypeFilter(QStringList value);
};

#endif // SALEDOCUMENTTVMODEL_H
