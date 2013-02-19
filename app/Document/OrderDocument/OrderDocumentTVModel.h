#ifndef ORDERDOCUMENTTVMODEL_H
#define ORDERDOCUMENTTVMODEL_H

#include "Document/DocumentTVModel.h"
#include "Document/DocumentTVDisplayer.h"

class OrderDocumentTVModel : public DocumentTVModel
{
    void initHeaders();

public:
    OrderDocumentTVModel();
    ~OrderDocumentTVModel();

    void getDocuments();


};

#endif // ORDERDOCUMENTTVMODEL_H
