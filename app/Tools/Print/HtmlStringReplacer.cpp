#include "HtmlStringReplacer.h"

HtmlStringReplacer::HtmlStringReplacer()
{
}

void HtmlStringReplacer::setCopyOrOriginal(QString copyOrOriginal)
{
    htmlCode.replace("%copyORoriginal",copyOrOriginal);
}

void HtmlStringReplacer::setMyCompany(Owner data)
{  if(data.getName().isEmpty())
        htmlCode.replace("%my_companyname%","");
   else
        htmlCode.replace("%my_companyname%",data.getName()+"<br>");

   if(data.getAdress().isEmpty())
        htmlCode.replace("%my_address%","");
   else
       htmlCode.replace("%my_address%",data.getAdress());

   if(data.getPostCode().isEmpty())
       htmlCode.replace("%my_postcode%","");
   else
        htmlCode.replace("%my_postcode%",data.getPostCode());

   if(data.getCity().isEmpty())
       htmlCode.replace("%my_city%","");
   else
        htmlCode.replace("%my_city%",data.getCity()+"<br>");

   if(!data.getPhone(0).isEmpty())
        htmlCode.replace("%my_phone%","Tel.: " +data.getPhone(0)+",\n<br>");

   if(!data.getPhone(1).isEmpty())
        htmlCode.replace("%my_phone1%","Tel.: " +data.getPhone(1)+",<br>");

   if (!data.getPhone(2).isEmpty())
        htmlCode.replace("%my_phone2%","Tel.: " +data.getPhone(2)+"<br>");

   if (data.getPhone(0).isEmpty())
       htmlCode.replace("%my_phone%"," ");
   if(data.getPhone(1).isEmpty())
        htmlCode.replace("%my_phone1%"," ");
   if(data.getPhone(2).isEmpty())
        htmlCode.replace("%my_phone2%"," ");

   if(data.getNIP().isEmpty())
       htmlCode.replace("%my_nip%","");
   else
        htmlCode.replace("%my_nip%","NIP: " + data.getNIP())+"<br>";

   if(data.getBankName().isEmpty())
       htmlCode.replace("%my_bankname%","");
   else
   htmlCode.replace("%my_bankname%",data.getBankName()+"<br>");

   if(data.getBankAccount().isEmpty())
       htmlCode.replace("%my_bankaccount%"," ");
   else
        htmlCode.replace("%my_bankaccount%",data.getBankAccount()+"<br>");
   if(data.getAdditional().isEmpty())
       htmlCode.replace("%additional%"," ");
   else
       htmlCode.replace("%additional%",data.getAdditional());

}

void HtmlStringReplacer::setIssuePlace(QString data)
{
    htmlCode.replace("%issue_place%",data);
}

void HtmlStringReplacer::setPriceOption(QString data,bool type)
{   isNet = type;
    htmlCode.replace("%headPrice%",data);
}

void HtmlStringReplacer::setSaleDate(QString data)
{
    htmlCode.replace("%sale_date%",data);
}

void HtmlStringReplacer::setIssueDate(QString data)
{
    htmlCode.replace("%issue_date%",data);
}

void HtmlStringReplacer::setPaymentDate(QString data)
{
    htmlCode.replace("%payment_date%",data);
}

void HtmlStringReplacer::setBuyerInfo(Contractor data)
{
    htmlCode.replace("%buyer_companyname%", data.getName());
    htmlCode.replace("%buyer_address%", data.getAddress());
    htmlCode.replace("%buyer_postcode%", data.getPostcode());
    htmlCode.replace("%buyer_city%", data.getCity());

    if(data.getNip().isEmpty())
        htmlCode.replace("%buyer_nip%", "");
    else
        htmlCode.replace("%buyer_nip%", "NIP: " +data.getNip());
}

void HtmlStringReplacer::setBuyerInfo(Owner data)
{   if(data.getName().isEmpty())
        htmlCode.replace("%my_companyname%","");
    else
        htmlCode.replace("%buyer_companyname%", data.getName());

    if(data.getAdress().isEmpty())
        htmlCode.replace("%buyer_address%", "");
    else
        htmlCode.replace("%buyer_address%", data.getAdress());

    if(data.getPostCode().isEmpty())
        htmlCode.replace("%buyer_postcode%", "");
    else
        htmlCode.replace("%buyer_postcode%", data.getPostCode());

    if(data.getCity().isEmpty())
        htmlCode.replace("%buyer_city%", "");
    else
        htmlCode.replace("%buyer_city%", data.getCity());

    if(data.getNIP().isEmpty())
        htmlCode.replace("%buyer_nip%", "");
    else
        htmlCode.replace("%buyer_nip%", data.getNIP());

}

void HtmlStringReplacer::setDocumentName(QString data)
{
    htmlCode.replace("%document_name%",data);
}
void HtmlStringReplacer::setStoreDate(QString data)
{
    htmlCode.replace("%storeDate%",data);
}
void HtmlStringReplacer::setTransport(QString data)
{
    htmlCode.replace("%transport%",data);
}

void HtmlStringReplacer::setShipping(QString data)
{
    htmlCode.replace("%shipping%",data);
}

void HtmlStringReplacer::setWaybill(QString data)
{
    htmlCode.replace("%waybill%",data);
}
void HtmlStringReplacer::setDocumentNumer(QString data)
{
    htmlCode.replace("%document_number%",data);
}
void HtmlStringReplacer::setIssueName(QString data)
{
    htmlCode.replace("%issue_name%", data);
}
void HtmlStringReplacer::setRole1(QString data)
{
    htmlCode.replace("%role1%", data);
}
void HtmlStringReplacer::setRole2(QString data)
{
    htmlCode.replace("%role2%", data);
}
void HtmlStringReplacer::setReceiverName(QString data)
{
    htmlCode.replace("%receiver_name%",data);
}
void HtmlStringReplacer::setToPay(double data)
{
    htmlCode.replace("%toPay%",QString::number(data,'.',2));
}
void HtmlStringReplacer::setToPayWords(QString data)
{
    htmlCode.replace("%toPayWords%",data);
}
void HtmlStringReplacer::setLogoPathOwner(QString logoPath)
{
    htmlCode.replace("%logoPath%", "file://" + logoPath);
}

void HtmlStringReplacer::setSummaryValue (double data)
{
    htmlCode.replace("%summary_value%",QString::number(data,',',2).replace(".", ","));
}
void HtmlStringReplacer::setSummaryValueWord(QString data)
{
    htmlCode.replace("%summary_words%",data);
}
void HtmlStringReplacer::setWord(QString data)
{
    htmlCode.replace("%words%",data);
}
void HtmlStringReplacer::setDocTypeComment(QString data)
{
    htmlCode.replace("%docTypeComment%",data);
}
void HtmlStringReplacer::setMethodOfPayment(QString data)
{
    htmlCode.replace("%method_of_payment%",data);
}
void HtmlStringReplacer::setSignature(QString type)
{
    DocumentInfoModel *documentInfoModel = new DocumentInfoModel();
    QString signature = documentInfoModel->getDocumentInfo(type).getAfterText();
    delete documentInfoModel;

    htmlCode.replace("%signature%", signature);
}
void HtmlStringReplacer::setSymbol(QString symbol)
{
    this->symbol=symbol;
}
void HtmlStringReplacer::setRealizationDate(QString data)
{
    htmlCode.replace("%realization_date%",data);
}
void HtmlStringReplacer::setInvoiceSymbol(QString data)
{htmlCode.replace("%invoice_symbol%",data);}
void HtmlStringReplacer::setInvoiceSaleDate(QString data)
{htmlCode.replace("%invoice_sale_date%",data);}
void HtmlStringReplacer::setInvoiceIssueDate(QString data)
{htmlCode.replace("%invoice_issue_date%",data);}
void HtmlStringReplacer::setCorrectedContent(QString data)
{htmlCode.replace("%corrected_content%",data);}
void HtmlStringReplacer::setCorrectContent(QString data)
{htmlCode.replace("%correct_content%",data);}
