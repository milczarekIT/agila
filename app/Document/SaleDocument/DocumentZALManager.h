#ifndef DocumentZALMANAGER_H
#define DocumentZALMANAGER_H

#include "Document/DocumentManager.h"

class DocumentZALManager : public DocumentManager
{

public:
    DocumentZALManager();
    ~DocumentZALManager();

    void setContractor(Contractor c);
    Contractor getContractor();
    void countGoodsValue(double discountPercentage);

};

#endif // DocumentZALMNAGER_H
