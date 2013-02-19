#ifndef PRICEDOCUMENTTVMODEL_H
#define PRICEDOCUMENTTVMODEL_H

#include "Document/DocumentTVModel.h"
class PriceDocumentTVModel : public DocumentTVModel
{

private:
    void initHeaders();

public:
    PriceDocumentTVModel();
    ~PriceDocumentTVModel();
    void getDocuments();
    void setDocTypeFilter(QString value);
    void setDocTypeFilter(QStringList value);
};

#endif // PRICEDOCUMENTTVMODEL_H
