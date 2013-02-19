#include "PrintPurchaseDocumentManager.h"

PrintPurchaseDocumentManager::PrintPurchaseDocumentManager()
{
}

void PrintPurchaseDocumentManager::print(PurchaseInvoice *document,QString copyOrOriginal,QPrinter* drukarka)
{
    if(document->getSymbol().contains("FZ")){
        getEngine()->setSymbol("FZ");
        this->prepareToPrint("Faktura VAT Zakupu ",document,copyOrOriginal,drukarka);
    }

    if(document->getSymbol().contains("RR")){
        getEngine()->setSymbol("RR");
        this->prepareToPrint("Faktura VAT RR ",document,copyOrOriginal,drukarka);
    }

}

void PrintPurchaseDocumentManager::prepareToPrint(QString name,PurchaseInvoice *document,QString copyOrOriginal,QPrinter* drukarka)
{
    getEngine()->loadTemplate("PurchaseInvoice");
    getEngine()->setDocumentName(name);
    printPurchaseDocument(document,copyOrOriginal,drukarka);

}

void PrintPurchaseDocumentManager::printPurchaseDocument(PurchaseInvoice *document,QString copyOrOriginal,QPrinter *drukarka)
{
    priceType();
    Owner owner = getOwnerService()->getActualOwner();
    getEngine()->setMyCompany(owner);
    getEngine()->setLogoPathOwner(owner.getLogoPath());
    getEngine()->setMyCompany(getOwnerService()->getActualOwner());
    getEngine()->setCopyOrOriginal(copyOrOriginal);
    getEngine()->setIssuePlace(document->getDocumentPlace());
    getEngine()->setSaleDate(document->getSaleDate().toString("dd.MM.yyyy"));
    getEngine()->setIssueDate(document->getDocumentDate().toString("dd.MM.yyyy"));
    getEngine()->setPaymentDate(document->getPaymentDate().toString("dd.MM.yyyy"));
    getEngine()->setBuyerInfo(document->getContractor());
    getEngine()->setDocumentNumer(document->getSymbol());
    getEngine()->setSummaryValue(document->getTotal());
    getEngine()->setIssueName(document->getIssueName());
    getEngine()->setReceiverName(document->getReceiveName());
    getEngine()->setMethodOfPayment(document->getMethodOfPayment().getName());
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

void PrintPurchaseDocumentManager::print(DocumentNK *document,QString copyOrOriginal,QPrinter* drukarka)
{
    getEngine()->setSymbol("NK");
    getEngine()->loadTemplate("NK");
    getEngine()->setCopyOrOriginal(copyOrOriginal);
    getEngine()->setIssuePlace(document->getDocumentPlace());
    getEngine()->setIssueDate(document->getDocumentDate().toString("dd.MM.yyyy"));
    getEngine()->setBuyerInfo(document->getContractor());
    getEngine()->setDocumentNumer(document->getSymbol());
    Owner owner = getOwnerService()->getActualOwner();
    getEngine()->setMyCompany(owner);
    getEngine()->setLogoPathOwner(owner.getLogoPath());
    getEngine()->setInvoiceSymbol(document->getInvoiceSymbol());
    getEngine()->setInvoiceSaleDate(document->getDocumentDate().toString("dd.MM.yyyy"));
    getEngine()->setInvoiceIssueDate(document->getInvoiceDate().toString("dd.MM.yyyy"));
    getEngine()->setCorrectedContent(document->getCorrectedContent());
    getEngine()->setCorrectContent(document->getCorrectContent());
    getEngine()->setIssueName(document->getIssueName());
    getEngine()->setReceiverName(document->getReceiveName());
    getEngine()->setSignature(document->getDocumentType());
    getEngine()->print(drukarka);

}

void PrintPurchaseDocumentManager::print(DocumentFZK *document,QString copyOrOriginal, QPrinter *drukarka)
{
        QVector< QPair<int, int> > list;
        QVector< QPair<int, int> > list2;
        getEngine()->setSymbol("FZK");
        getEngine()->loadTemplate("FZK");
        priceType();
        getEngine()->setCopyOrOriginal(copyOrOriginal);
        Owner owner = getOwnerService()->getActualOwner();
        getEngine()->setMyCompany(owner);
        getEngine()->setLogoPathOwner(owner.getLogoPath());
        getEngine()->setIssuePlace(document->getDocumentPlace());
        getEngine()->setSaleDate(document->getSaleDate().toString("dd.MM.yyyy"));
        getEngine()->setIssueDate(document->getDocumentDate().toString("dd.MM.yyyy"));
        getEngine()->setPaymentDate(document->getPaymentDate().toString("dd.MM.yyyy"));
        getEngine()->setBuyerInfo(document->getContractor());
        getEngine()->setDocumentNumer(document->getSymbol());
        getEngine()->setDocTypeComment("Do dokumentu: "+document->getInvoice().getSymbol());
        getEngine()->setIssueName(document->getIssueName());
        getEngine()->setReceiverName(document->getReceiveName());
        getEngine()->setSignature(document->getDocumentType());
        getEngine()->setSummaryValue(document->getTotal());
        if(document->getTotal()<0)
            getEngine()->setWord("Słownie do zwrotu: ");
        else
            getEngine()->setWord("Słownie: ");
        getEngine()->setSummaryValueWord(getNumberToWords()->toWords(document->getTotal()));
        getEngine()->setMethodOfPayment(document->getMethodOfPayment().getName());

        for (int i=0 ; i<document->getInvoice().getDocumentPositions().size();i++)
        {
            QPair<int, int> p;
            p.first=i; p.second=-1;
            list.push_back(p);
            list2.push_back(p);
        }

        getEngine()->setHtml();
        for (int i=0 ; i<document->getDocumentPositions().size();i++)
        {bool found=false;

            for (int j=0 ; j<list2.size();j++)
            {
                if(document->getInvoice().getDocumentPositions()[list2[j].first].getGood().getId()
                    ==document->getDocumentPositions()[i].getGood().getId())
                {
                    found = true;
                    list[j].second=i;
                }
            }
            if(!found)
            {
                QPair<int, int> p;
                p.first=-1; p.second=i;
                list.push_back(p);
            }
        }
    for (int i=0 ;i<list.size();i++){
        if (list[i].first!=-1 && list[i].second!=-1)
            getEngine()->addCorrectionPosition(&document->getInvoice().getDocumentPositions()[list[i].first]
                                       ,&document->getDocumentPositions()[list[i].second],document->getDiscount());
        else if (list[i].first==-1)
            getEngine()->addCorrectionPosition(0,&document->getDocumentPositions()[list[i].second],document->getDiscount());
        else if(list[i].second==-1)
            getEngine()->addCorrectionPosition(&document->getInvoice().getDocumentPositions()[list[i].first],0,document->getDiscount());
    }

        getEngine()->print(drukarka,document->getInvoice().isPaid());
}
