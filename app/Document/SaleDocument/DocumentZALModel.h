#ifndef DOCUMENTZALMODEL_H
#define DOCUMENTZALMODEL_H

#include "Contractor/Contractor.h"
#include "Contractor/ContractorService.h"
#include "Settings/SettingsModel.h"
#include "Document/DocumentModel.h"
#include "Document/MOPModel.h"
#include "Document/SaleDocument/DocumentZAL.h"

class DocumentZALModel : public DocumentModel
{
public:
    DocumentZALModel();
    ~DocumentZALModel();

    DocumentZAL getDocumentZAL(QString symbol);
    void addDocumentZAL(DocumentZAL document);
    void editDocumentZAL(DocumentZAL document);
    void removeDocumentZAL(QString symbol);
};

#endif // DOCUMENTZALMODEL_H
