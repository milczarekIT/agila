#include "PrintSaleDocumentManager.h"

PrintSaleDocumentManager::PrintSaleDocumentManager()
{
}
void PrintSaleDocumentManager::print(Invoice *document,QString copyOrOriginal,QPrinter* drukarka)
{
    if(document->getSymbol().contains("FV")){
        getEngine()->setSymbol("FV");
        this->prepareToPrint("Faktura VAT ",document,copyOrOriginal,drukarka);}

    if(document->getSymbol().contains("PA")){
        getEngine()->setSymbol("PA");
        getEngine()->loadTemplate("PA");
        printSaleDocument(document,copyOrOriginal,drukarka);
    }

    if(document->getSymbol().contains("PI")){
         getEngine()->setSymbol("PI");
        this->prepareToPrint("Paragon ",document,copyOrOriginal,drukarka);
       }

    if(document->getSymbol().contains("PRO")){
        this->prepareToPrint("Faktura PROFORMA ",document,copyOrOriginal,drukarka);
        getEngine()->setSymbol("PRO");
    }

    if(document->getSymbol().section('/',0,0) =="FMP"){
        getEngine()->setSymbol("FMP");
        this->prepareToPrint("Faktura VAT-MP ",document,copyOrOriginal,drukarka);
    }

    if(document->getSymbol().section('/',0,0)=="FM"){
        getEngine()->setSymbol("FM");
        if(copyOrOriginal=="ORYGINAŁ")
            getEngine()->loadTemplate("FM");
        else
            getEngine()->loadTemplate("FM_ZAL");
        printSaleDocument(document,copyOrOriginal,drukarka);
    }
}

void PrintSaleDocumentManager::prepareToPrint(QString name,Invoice *document,QString copyOrOriginal,QPrinter* drukarka)
{
    getEngine()->loadTemplate("Invoice");
    getEngine()->setDocumentName(name);
    printSaleDocument(document,copyOrOriginal,drukarka);

}

void PrintSaleDocumentManager::printZAL(DocumentZAL *document,QString copyOrOriginal, QPrinter *drukarka)
{
    priceType();
    Owner owner = getOwnerService()->getActualOwner();
    getEngine()->setMyCompany(owner);
    getEngine()->setLogoPathOwner(owner.getLogoPath());
    getEngine()->setCopyOrOriginal(copyOrOriginal);
    getEngine()->setIssuePlace(document->getDocumentPlace());
    getEngine()->setSaleDate(document->getSaleDate().toString("dd.MM.yyyy"));
    getEngine()->setIssueDate(document->getDocumentDate().toString("dd.MM.yyyy"));
    getEngine()->setPaymentDate(document->getPaymentDate().toString("dd.MM.yyyy"));
    getEngine()->setBuyerInfo(document->getContractor());
    getEngine()->setDocumentNumer(document->getSymbol());
    getEngine()->setIssueName(document->getIssueName());
    getEngine()->setReceiverName(document->getReceiveName());
    getEngine()->setMethodOfPayment(document->getMethodOfPayment().getName());
    getEngine()->setSignature(document->getDocumentType());
    getEngine()->setToPay(countToPay(document->getDocumentPositions(),document->getPreviousDocumentsZAL(),document->getDiscount())-document->getPaidValue());
    getEngine()->setToPayWords(getNumberToWords()->toWords(countToPay(document->getDocumentPositions(),document->getPreviousDocumentsZAL(),document->getDiscount())-document->getPaidValue()));
    if(document->getTotal()<0)
        getEngine()->setWord("Słownie do zwrotu: ");
    else
        getEngine()->setWord("Słownie: ");
    getEngine()->setSummaryValueWord(getNumberToWords()->toWords(document->getPaidValue()));
    getEngine()->setSummaryValue(document->getPaidValue());
    getEngine()->setHtml();
    for (int i=0 ; i<document->getDocumentPositions().size() ; i++)
         getEngine()->addDocumentPosition(&document->getDocumentPositions()[i],document->getDiscount());
    for (int i=0; i<document->getPreviousDocumentsZAL().size();i++)
       getEngine()->addPreviousAdvances(&document->getPreviousDocumentsZAL()[i]);


    getEngine()->print(drukarka);
}

double PrintSaleDocumentManager::countToPay(QVector<DocumentPosition> documentPosition,QVector<SimpleDocumentInfo> previous,double discount)
{
    double total=0.0;
    double totalPrevious=0.0;
    double discountValue=0.0;
    double totalWithDiscount=0.0;
    for (int i=0; i<documentPosition.size(); i++)
    {
    total+=(documentPosition[i].getPriceGross())*(documentPosition[i].getQuantity());
    } discountValue=total*(discount/100);
    totalWithDiscount = total-discountValue;
    for (int i=0; i<previous.size(); i++)
    {
    totalPrevious+=previous[i].getTotal();
    }

    return totalWithDiscount-totalPrevious;
}

void PrintSaleDocumentManager::print(DocumentZAL *document,QString copyOrOriginal, QPrinter *drukarka)
{
    getEngine()->loadTemplate("ZAL");
    if(document->getDocumentType().contains("ZAL"))
    {
        getEngine()->setSymbol("FV");
        getEngine()->setDocumentName("Faktura VAT Zaliczka");
    }
    else if(document->getDocumentType().contains("RZL"))
    {
        getEngine()->setSymbol("FV");
        getEngine()->setDocumentName("Faktura VAT Końcowa");
    }
    printZAL(document,copyOrOriginal,drukarka);
}

void PrintSaleDocumentManager::printSaleDocument(Invoice *document,QString copyOrOriginal,QPrinter *drukarka)
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

void PrintSaleDocumentManager::print(DocumentFK *document,QString copyOrOriginal, QPrinter *drukarka)
{
    priceType();
    QVector< QPair<int, int> > list;
    QVector< QPair<int, int> > list2;
    getEngine()->setSymbol("FK");
    getEngine()->loadTemplate("FK");
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

    for (int i=0 ;i<list.size();i++) {
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
