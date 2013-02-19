#ifndef DocumentZALPolicy_H
#define DocumentZALPolicy_H

#include "Document/SaleDocument/DocumentZAL.h"

class DocumentZALPolicy
{
public:
    DocumentZALPolicy();
    ~DocumentZALPolicy();
    DocumentZAL getDocumentZAL();
    DocumentZAL getOldDocumentZAL();
    void setDocumentZAL(DocumentZAL documentZAL);
    void setOldDocumentZAL(DocumentZAL documentZALOld);
    void setContractor(Contractor c);
    void setPreviousZAL(QVector <SimpleDocumentInfo> previous);
    void setPreviousZALVector(QVector <SimpleDocumentInfo> previous);
    QVector<SimpleDocumentInfo> getPreviousZAL();
    Contractor getContractor();
    virtual void setDocumentData(DocumentZAL doc);
    void appendToPrevious(SimpleDocumentInfo simple);
    QVector<SimpleDocumentInfo> getPreviousZALVector();
    void removeFromVector(int id);
private:
    DocumentZAL documentZAL,oldDocumentZAL;
    QVector<SimpleDocumentInfo> previous;
};

#endif // DocumentZALPolicy_H
