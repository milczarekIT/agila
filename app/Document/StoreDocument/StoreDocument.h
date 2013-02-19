#ifndef STOREDOCUMENT_H
#define STOREDOCUMENT_H

#include "Document/Document.h"

class StoreDocument : public Document
{
public:
    StoreDocument();
    ~StoreDocument();
    void setDepartment(SimpleStructure department);
    SimpleStructure getDepartment();
    int operator==(StoreDocument in);

private:
    SimpleStructure department;

};

#endif // STOREDOCUMENT_H
