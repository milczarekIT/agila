#ifndef DOCUMENTPZPOLICY_H
#define DOCUMENTPZPOLICY_H

#include "Document/StoreDocument/DocumentPZ.h"

class DocumentPZPolicy
{
public:
    DocumentPZPolicy();
    ~DocumentPZPolicy();
    DocumentPZ getDocumentPZ();
    DocumentPZ getOldDocumentPZ();
    void setDocumentPZ(DocumentPZ documentPZ);
    void setOldDocumentPZ(DocumentPZ documentPZOld);
    void setContractor(Contractor c);
    Contractor getContractor();
    void setDocumentData(DocumentPZ doc);

private:

    DocumentPZ documentPZ,documentPZOld;
};

#endif // DOCUMENTPZPOLICY_H
