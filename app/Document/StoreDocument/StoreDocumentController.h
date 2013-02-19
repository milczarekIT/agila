#ifndef STOREDOCUMENTCONTROLLER_H
#define STOREDOCUMENTCONTROLLER_H

#include "Document/DocumentController.h"

class StoreDocumentController : public DocumentController
{

public:
    explicit StoreDocumentController();
    ~StoreDocumentController();

protected:

    void addGood();
    bool isQuantityColumn(int column);
    void setGoodsValue();

};

#endif // STOREDOCUMENTCONTROLLER_H
