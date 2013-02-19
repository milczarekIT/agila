#ifndef DOCUMENTWZPOLICY_H
#define DOCUMENTWZPOLICY_H

#include "Document/StoreDocument/DocumentWZ.h"

class DocumentWZPolicy
{
public:
    DocumentWZPolicy();
    ~DocumentWZPolicy();
    DocumentWZ getDocumentWZ();
    DocumentWZ getOldDocumentWZ();
    void setDocumentWZ(DocumentWZ documentWZ);
    void setOldDocumentWZ(DocumentWZ documentWZOld);
    void setContractor(Contractor c);
    Contractor getContractor();
    void setDocumentData(DocumentWZ doc);

private:

    DocumentWZ documentWZ,documentWZOld;
};

#endif // DOCUMENTPZPOLICY_H
