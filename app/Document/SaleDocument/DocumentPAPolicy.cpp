#include "DocumentPAPolicy.h"

DocumentPAPolicy::DocumentPAPolicy()
{
}

void DocumentPAPolicy::setDocumentData(Invoice doc)
{

    invoice.setDocumentType(doc.getDocumentType());
    invoice.setSymbol(doc.getSymbol());
    invoice.setDocumentPlace(doc.getDocumentPlace());
    invoice.setDocumentDate(doc.getDocumentDate());
    invoice.setSaleDate(doc.getSaleDate());
    invoice.setTotal(doc.getTotal());
    invoice.setDiscount(doc.getDiscount());
    invoice.setIssueName(doc.getIssueName());
    invoice.setStoreResult(doc.getStoreResult());
    invoice.setOrder(doc.getOrder());
    invoice.setDocumentPositions(doc.getDocumentPositions());

}
