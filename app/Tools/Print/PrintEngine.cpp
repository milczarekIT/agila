#include "PrintEngine.h"

PrintEngine::PrintEngine()
{
}
bool PrintEngine::loadTemplate(QString templatePrefix)
{
    this->templatePrefix = templatePrefix;
    QFile file(":/document-templates/" + templatePrefix +"-template.htm");
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
           htmlCode = file.readAll();
           isSetHtml=false;
           return true;
        }
        return false;

}
void PrintEngine::positionToDOM(QDomDocument &doc, QDomElement &node, DocumentPosition *data, float discount )
{
        QDomElement good_name = doc.createElement( "good_name" );
        good_name.appendChild(doc.createTextNode(data->getGood().getName()));
        node.appendChild(good_name);
        QDomElement good_pkwiu = doc.createElement( "good_pkwiu" );
        if(data->getGood().getPkwiu()=="")
            good_pkwiu.appendChild(doc.createTextNode("0"));
        else
            good_pkwiu.appendChild(doc.createTextNode(data->getGood().getPkwiu()));
        node.appendChild(good_pkwiu);
        QDomElement good_unit = doc.createElement( "good_unit" );
        good_unit.appendChild(doc.createTextNode(data->getGood().getUnit().getName()));
        node.appendChild(good_unit);
        QDomElement good_quantity = doc.createElement( "good_quantity" );
        good_quantity.appendChild(doc.createTextNode(QString::number(data->getQuantity())));
        node.appendChild(good_quantity);
        QDomElement good_discount = doc.createElement( "good_discount" );
        good_discount.appendChild(doc.createTextNode(QString::number(discount,',',2)));
        node.appendChild(good_discount);

        if(this->symbol=="FM")
        {
            QDomElement good_pricegross = doc.createElement( "good_pricegross" );
            good_pricegross.appendChild(doc.createTextNode(QString::number(data->getGood().getPriceNet(Price::MAG).value(),',',2)));
            node.appendChild(good_pricegross);
        }
            else
        {
        QDomElement good_pricegross = doc.createElement( "good_pricegross" );
        good_pricegross.appendChild(doc.createTextNode(QString::number(data->getPriceGross())));
        node.appendChild(good_pricegross);
        }
        QDomElement good_tax = doc.createElement( "good_tax" );
        good_tax.appendChild(doc.createTextNode(QString::number(data->getTax().getValue())));
        node.appendChild(good_tax);
        QDomElement good_tax_short = doc.createElement("tax_short");
        good_tax_short.appendChild(doc.createTextNode(data->getTax().getShortName()));
        node.appendChild(good_tax_short);
        QDomElement good_taxname = doc.createElement( "good_taxname" );
        good_taxname.appendChild(doc.createTextNode(data->getTax().getName()));
        node.appendChild(good_taxname);
        double brutval=0.0;
        double vatval=0.0;
        double netval=0.0;
        if(isNet)
        {

            QDomElement good_pricenet = doc.createElement( "good_pricenet" );
            good_pricenet.appendChild(doc.createTextNode(QString::number(data->getPriceNet(),',',2)));
            node.appendChild(good_pricenet);

            netval =data->getPriceNet()* data->getQuantity();
            QDomElement good_netval = doc.createElement( "netval" );
            good_netval.appendChild(doc.createTextNode(QString::number(netval,',',2)));
            node.appendChild(good_netval);

            vatval =netval * data->getTax().getValue()/100;
            QDomElement good_vatval = doc.createElement( "vatval" );
            good_vatval.appendChild(doc.createTextNode(QString::number(vatval,',',2)));
            node.appendChild(good_vatval);

            brutval =netval +vatval;
            QDomElement good_brutval = doc.createElement( "brutval" );
            good_brutval.appendChild(doc.createTextNode(QString::number(brutval,',',2)));
            node.appendChild(good_brutval);
        }
        else
        {

            QDomElement good_pricenet = doc.createElement( "good_pricenet" );
            good_pricenet.appendChild(doc.createTextNode(QString::number(data->getPriceGross(),',',2)));
            node.appendChild(good_pricenet);

            brutval =data->getPriceGross()* data->getQuantity();
            QDomElement good_brutval = doc.createElement( "brutval" );
            good_brutval.appendChild(doc.createTextNode(QString::number(brutval,',',2)));
            node.appendChild(good_brutval);

            vatval =brutval*(data->getTax().getValue()/(100+data->getTax().getValue()));
            QDomElement good_vatval = doc.createElement( "vatval" );
            good_vatval.appendChild(doc.createTextNode(QString::number(vatval,',',2)));
            node.appendChild(good_vatval);

            netval = brutval-vatval;
            QDomElement good_netval = doc.createElement( "netval" );
            good_netval.appendChild(doc.createTextNode(QString::number(netval,',',2)));
            node.appendChild(good_netval);
        }
        if(this->symbol=="FM")
        {
            double discountval = netval *(discount/100);
            QDomElement good_discountval = doc.createElement( "discountval" );
            good_discountval.appendChild(doc.createTextNode(QString::number(discountval,',',2)));
            node.appendChild(good_discountval);

            double marginbrut = netval -data->getGood().getPriceNet(Price::MAG).value();
            QDomElement good_marginbrut = doc.createElement( "marginbrut" );
            good_marginbrut.appendChild(doc.createTextNode(QString::number(marginbrut,',',2)));
            node.appendChild(good_marginbrut);

            double marginnet = marginbrut *(1-data->getTax().getValue()/100);
            QDomElement good_marginnet = doc.createElement( "marginnet" );
            good_marginnet.appendChild(doc.createTextNode(QString::number(marginnet,',',2)));
            node.appendChild(good_marginnet);
        }
            else
        {
        double discountval = brutval *(discount/100);
        QDomElement good_discountval = doc.createElement( "discountval" );
        good_discountval.appendChild(doc.createTextNode(QString::number(discountval,',',2)));
        node.appendChild(good_discountval);
        }
}
void PrintEngine::setHtml()
{
    if(isSetHtml==false){
        page.settings()->clearMemoryCaches();
        page.settings()->setMaximumPagesInCache(0);
        page.settings()->globalSettings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, true);
        page.settings()->globalSettings()->setAttribute(QWebSettings::LocalContentCanAccessFileUrls,true);
        page.settings()->globalSettings()->setAttribute(QWebSettings::PrintElementBackgrounds, true);
        page.settings()->globalSettings()->setAttribute(QWebSettings::AutoLoadImages, true);
        page.mainFrame()->setHtml(htmlCode);



        waitForLoad();

        hideLogoIfNotDefined(); // musi być bo setHtml

        isSetHtml=true;
    }
}

void PrintEngine::hideLogoIfNotDefined()
{
    QWebElement logo = page.mainFrame()->findFirstElement("img.logo");
    if(logo.attribute("src") == "file://")
        logo.setStyleProperty("display", "none");
}

void PrintEngine::waitForLoad()
{
    QEventLoop *loop = new QEventLoop();
    QObject::connect(&page, SIGNAL(loadFinished(bool)), loop, SLOT(quit()));

    QTimer *idleTimer = new QTimer(this);
    connect(idleTimer,SIGNAL(timeout()),loop,SLOT(quit()));
    idleTimer->setInterval(3 * 1000);

    idleTimer->start();
    loop->exec();
}

void PrintEngine::addDocumentPosition(DocumentPosition *data,float discount)
{
    QDomDocument dpos( "documentPosition" );
    QDomElement values = dpos.createElement( "values" );
    positionToDOM(dpos,values,data,discount);
    dpos.appendChild(values);
    page.mainFrame()->evaluateJavaScript("addDocPosition(\""  +dpos.toString(-1).remove("\n")+  "\")");

}

void PrintEngine::previousToDOM(QDomDocument &doc, QDomElement &node, SimpleDocumentInfo *data)
{
        QDomElement symbol = doc.createElement( "symbol" );
        symbol.appendChild(doc.createTextNode(data->getSymbol()));
        node.appendChild(symbol);
        QDomElement docDate= doc.createElement( "docDate" );
        docDate.appendChild(doc.createTextNode(QVariant(data->getDocumentDate()).toString()));
        node.appendChild(docDate);
        QDomElement total= doc.createElement( "total" );
        total.appendChild(doc.createTextNode(QString::number(data->getTotal())));
        node.appendChild(total);
}

void PrintEngine::addPreviousAdvances(SimpleDocumentInfo *data)
{

    if(isSetHtml==false){
        this->setHtml();
        isSetHtml=true;
    }
    QDomDocument prev( "previous" );
    QDomElement values = prev.createElement( "values" );
    previousToDOM(prev,values,data);
    prev.appendChild(values);
    page.mainFrame()->evaluateJavaScript("addPrevious(\""  +prev.toString(-1).remove("\n")+  "\")");

}

void PrintEngine::addCorrectionPosition(DocumentPosition *before, DocumentPosition *after, float discount)
{
    if(isSetHtml==false){
        this->setHtml();
        isSetHtml=true;
    }
    QDomDocument dpos( "documentPosition" );
    QDomElement values =dpos.createElement("values");
    QDomElement dom_before = dpos.createElement( "before" );
    QDomElement dom_after = dpos.createElement( "after" );
    if(before!=0)
    {
    positionToDOM(dpos,dom_before,before,discount);
    values.appendChild(dom_before);
    }
    if(after!=0)
    {
    positionToDOM(dpos,dom_after,after,discount);
    values.appendChild(dom_after);
    }
    dpos.appendChild(values);

    page.mainFrame()->evaluateJavaScript("addDocPosition(\""  +dpos.toString(-1).remove("\n")+  "\")");
}

void PrintEngine::print(QPrinter* drukarka,bool paid)
{

    if(isSetHtml==false){
        page.mainFrame()->setHtml(htmlCode);
        isSetHtml=true;
    }
        page.mainFrame()->evaluateJavaScript("finalize(\""+ QVariant(paid).toString() +"\")");
        page.mainFrame()->print(drukarka);
}
