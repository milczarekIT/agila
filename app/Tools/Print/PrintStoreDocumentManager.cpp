#include "PrintStoreDocumentManager.h"

PrintStoreDocumentManager::PrintStoreDocumentManager()
{
}

void PrintStoreDocumentManager::printStoreDocument(StoreDocument *document,QString copyOrOriginal, QPrinter *drukarka)
{

    Owner owner = getOwnerService()->getActualOwner();
    getEngine()->setMyCompany(owner);
    getEngine()->setLogoPathOwner(owner.getLogoPath());
    getEngine()->setCopyOrOriginal(copyOrOriginal);
    getEngine()->setIssuePlace(document->getDocumentPlace());
    getEngine()->setIssueDate(document->getDocumentDate().toString("dd.MM.yyyy"));
    getEngine()->setBuyerInfo(owner); //Dokumenty magazynowe są w tej samej firmie pomiędzy magazynami jedynie
    getEngine()->setDocumentNumer(document->getSymbol());
    getEngine()->setSummaryValue(document->getTotal());
    getEngine()->setIssueName(document->getIssueName());
    getEngine()->setSignature(document->getDocumentType());
    if(document->getTotal()<0)
        getEngine()->setWord("Słownie do zwrotu: ");
    else
        getEngine()->setWord("Słownie: ");
    getEngine()->setSummaryValueWord(getNumberToWords()->toWords(document->getTotal()));
    getEngine()->setHtml();
    for (int i=0 ; i<document->getDocumentPositions().size() ; i++)
         getEngine()->addDocumentPosition(&document->getDocumentPositions()[i]);
    getEngine()->print(drukarka);
}

void PrintStoreDocumentManager::print(StoreDocument* document,QString copyOrOriginal,QPrinter* drukarka)
{
    if(document->getSymbol().contains("RW"))
    {
        getEngine()->setSymbol("RW");
        this->prepareToPrint("Rozchód wewnętrzny ",document,copyOrOriginal,drukarka);
        getEngine()->setRole1("Wydający");
        getEngine()->setRole2("Odbierający");

    }
    if(document->getSymbol().contains("PW"))
    {
        getEngine()->setSymbol("PW");
        this->prepareToPrint("Przychód wewnętrzny ",document,copyOrOriginal,drukarka);
        getEngine()->setRole2("Wydający");
        getEngine()->setRole1("Odbierający");

    }
    if(document->getSymbol().contains("MM"))
    {
        getEngine()->setSymbol("MM");
        this->prepareToPrint("Wydanie między magazynowe ",document,copyOrOriginal,drukarka);
        getEngine()->setRole1("Wydający");
        getEngine()->setRole2("Odbierający");

    }
}

void PrintStoreDocumentManager::prepareToPrint(QString name,StoreDocument *document, QString copyOrOriginal, QPrinter *drukarka)
{
    getEngine()->loadTemplate("Warehouse");
    getEngine()->setDocumentName(name);
    setRoles(name);
    printStoreDocument(document,copyOrOriginal,drukarka);
}

void PrintStoreDocumentManager::setRoles(QString name)
{

        if(name=="Rozchód wewnętrzny ")
        {
        getEngine()->setRole1("Wydający");
        getEngine()->setRole2("Odbierający");
         }


        if(name=="Przychód wewnętrzny ")
        {
        getEngine()->setRole2("Wydający");
        getEngine()->setRole1("Odbierający");
        }

        if(name=="Wydanie między magazynowe ")
        {
        getEngine()->setRole1("Wydający");
        getEngine()->setRole2("Odbierający");
       }
}

void PrintStoreDocumentManager::print(DocumentWZ *document,QString copyOrOriginal, QPrinter *drukarka)
{
    getEngine()->setSymbol("WZ");
    getEngine()->loadTemplate("WZ");
    getEngine()->setCopyOrOriginal(copyOrOriginal);
    Owner owner = getOwnerService()->getActualOwner();
    getEngine()->setMyCompany(owner);
    getEngine()->setLogoPathOwner(owner.getLogoPath());
    getEngine()->setIssuePlace(document->getDocumentPlace());
    getEngine()->setSaleDate(document->getSendDate().toString("dd.MM.yyyy"));
    getEngine()->setIssueDate(document->getDocumentDate().toString("dd.MM.yyyy"));
    getEngine()->setBuyerInfo(document->getContractor());
    if(document->getTransport().getId() == 0)
    getEngine()->setTransport("Nie dotyczy");
    else
    getEngine()->setTransport(document->getTransport().getName());
    if (document->getShipping() == 1)
    getEngine()->setShipping("Magazynu");
    else if(document->getShipping() == 2)
    getEngine()->setShipping("Odbiorcy");
    else
    getEngine()->setShipping("Nie dotyczy");
    getEngine()->setWaybill(document->getWaybillNumber());
    getEngine()->setDocumentNumer(document->getSymbol());
    getEngine()->setDocTypeComment("Do dokumentu: "+document->getFactureSymbol());
    getEngine()->setIssueName(document->getIssueName());
    getEngine()->setReceiverName(document->getReceiveName());
    getEngine()->setSignature(document->getDocumentType());
    getEngine()->setSummaryValue(document->getTotal());
    if(document->getTotal()<0)
        getEngine()->setWord("Słownie do zwrotu: ");
    else
        getEngine()->setWord("Słownie: ");
    getEngine()->setSummaryValueWord(getNumberToWords()->toWords(document->getTotal()));
    getEngine()->setHtml();
    for (int i=0 ; i<document->getDocumentPositions().size() ; i++)
         getEngine()->addDocumentPosition(&document->getDocumentPositions()[i]);
    getEngine()->print(drukarka);
}

void PrintStoreDocumentManager::print(DocumentPZ *document,QString copyOrOriginal, QPrinter *drukarka)
{
    getEngine()->setSymbol("PZ");
    getEngine()->loadTemplate("PZ");
    getEngine()->setCopyOrOriginal(copyOrOriginal);
    Owner owner = getOwnerService()->getActualOwner();
    getEngine()->setMyCompany(owner);
    getEngine()->setLogoPathOwner(owner.getLogoPath());
    getEngine()->setIssuePlace(document->getDocumentPlace());
    getEngine()->setStoreDate(document->getStoreDate().toString("dd.MM.yyyy"));
    getEngine()->setIssueDate(document->getDocumentDate().toString("dd.MM.yyyy"));
    getEngine()->setBuyerInfo(document->getContractor());
    getEngine()->setTransport(document->getTransport().getName());
    getEngine()->setDocumentNumer(document->getSymbol());
    getEngine()->setIssueName(document->getIssueName());
    getEngine()->setReceiverName(document->getReceiveName());
    getEngine()->setSignature(document->getDocumentType());
    getEngine()->setSummaryValue(document->getTotal());
    if(document->getTotal()<0)
        getEngine()->setWord("Słownie do zwrotu: ");
    else
        getEngine()->setWord("Słownie: ");
    getEngine()->setSummaryValueWord(getNumberToWords()->toWords(document->getTotal()));
    getEngine()->setHtml();
    for (int i=0 ; i<document->getDocumentPositions().size() ; i++)
         getEngine()->addDocumentPosition(&document->getDocumentPositions()[i]);
    getEngine()->print(drukarka);
}
