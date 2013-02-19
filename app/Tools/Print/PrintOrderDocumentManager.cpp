#include "PrintOrderDocumentManager.h"

PrintOrderDocumentManager::PrintOrderDocumentManager()
{
}
void PrintOrderDocumentManager::print(Order *document,QString copyOrOriginal,QPrinter *drukarka)
{
    priceType();
    Owner owner = getOwnerService()->getActualOwner();
    getEngine()->setSymbol(document->getSymbol().section('/',0,0));
    getEngine()->loadTemplate("Order");
    if(document->getSymbol().contains("ZD"))
        getEngine()->setDocumentName("Zamówienie do dostawcy");
    else if(document->getSymbol().contains("ZK"))
        getEngine()->setDocumentName("Zamówienie od klienta");
    getEngine()->setMyCompany(owner);
    getEngine()->setLogoPathOwner(owner.getLogoPath());
    getEngine()->setMyCompany(getOwnerService()->getActualOwner());
    getEngine()->setCopyOrOriginal(copyOrOriginal);
    getEngine()->setIssuePlace(document->getDocumentPlace());
    getEngine()->setRealizationDate(document->getRealizationDate().toString("dd.MM.yyyy"));
    getEngine()->setIssueDate(document->getDocumentDate().toString("dd.MM.yyyy"));
    getEngine()->setBuyerInfo(document->getContractor());
    getEngine()->setDocumentNumer(document->getSymbol());
    getEngine()->setSummaryValue(document->getTotal());
    getEngine()->setIssueName(document->getIssueName());
    getEngine()->setReceiverName(document->getReceiveName());
    getEngine()->setSignature(document->getDocumentType());
    if(document->getTotal()<0)
        getEngine()->setWord("Słownie do zwrotu: ");
    else
        getEngine()->setWord("Słownie: ");
    getEngine()->setSummaryValueWord(getNumberToWords()->toWords(document->getTotal()));
    getEngine()->setHtml();
    for (int i=0 ; i<document->getDocumentPositions().size() ; i++)
         getEngine()->addDocumentPosition(&document->getDocumentPositions()[i],document->getDiscount());
    getEngine()->print(drukarka);
}
