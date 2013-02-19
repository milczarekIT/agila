#ifndef DOCUMENTZALSERVICE_H
#define DOCUMENTZALSERVICE_H

#include "Document/SaleDocument/DocumentZAL.h"
#include "Document/SaleDocument/DocumentZALModel.h"
#include "Document/DocumentService.h"

class DocumentZALService : public DocumentService
{
private:
    QVector<SimpleDocumentInfo> getPreviousDocumentZAL(QVector<SimpleDocumentInfo> relatedDocuments);
    void addLinksToPreviousDocumentsZAL(QString actualDocumentZAL, QVector<SimpleDocumentInfo> previousDocumentsZAL);
    void editLinksToPreviousDocumentsZAL(DocumentZAL newDocument, DocumentZAL oldDocument);
protected:
    DocumentZALModel *model;
    DocumentZAL document;

public:
    DocumentZALService();
    ~DocumentZALService();

    DocumentZAL getDocumentZAL(QString symbol);
    void addDocumentZAL(DocumentZAL document);
    void editDocumentZAL(DocumentZAL document);
    void removeDocumentZAL(QString symbol, bool cancelStoreResult = true);
};

#endif // DOCUMENTZALSERVICE_H
