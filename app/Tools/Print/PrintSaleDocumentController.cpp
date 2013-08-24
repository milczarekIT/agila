#include "PrintSaleDocumentController.h"

PrintSaleDocumentController::PrintSaleDocumentController(QString symbol) : PrintDialogController(symbol)
{
    setSaleManager(new PrintSaleDocumentManager());
}

void PrintSaleDocumentController::print(Invoice* document)
{
    setSymbol(document->getSymbol());
    setType(document->getDocumentType());
    int viewSignal=0;
    if(!getPrintReleated())
    {
        addDocToTable(document->getRelatedDocuments());
        viewSignal=getView()->exec();
    }

    if(viewSignal==1||getPrintReleated())
    {
        for(int i =0; i <getPrintAndSave();i++)
        {
            if(!getView()->isDuplicate())
                options(document->getSymbol(),i,"ORYGINAŁ");
            else
                options(document->getSymbol(),i,"DUPLIKAT");
            getSaleManager()->print(document,getCopyOrOriginal(),getPrinter());

            if(getSymbol().section("/",0,0)=="FM")
            {
                if(!getView()->isDuplicate())
                    options(document->getSymbol(),i,"ZAŁĄCZNIK");
                else
                    options(document->getSymbol(),i,"DUPLIKAT");

            }
            else
            {
                if(!getView()->isDuplicate())
                    options(document->getSymbol(),i,"KOPIA");
                else
                    options(document->getSymbol(),i,"DUPLIKAT");
            }
            for(int i=0;i<getView()->getSpinBox()->text().toInt();i++)
            {
                getSaleManager()->print(document,getCopyOrOriginal(),getPrinter());
            }
            setSaveToPdf(false);
        }
    }
    if(viewSignal!=0)
        printRelated(document->getRelatedDocuments());
}

void PrintSaleDocumentController::print(DocumentZAL *document)
{
    setSymbol(document->getSymbol());
    setType(document->getDocumentType());
    int viewSignal=0;
    if(!getPrintReleated())
    {
        addDocToTable(document->getRelatedDocuments());
        viewSignal=getView()->exec();
    }

    if(viewSignal==1||getPrintReleated())
    {
        for(int i =0; i <getPrintAndSave();i++)
        {
            if(!getView()->isDuplicate())
                options(document->getSymbol(),i,"ORYGINAŁ");
            else
                options(document->getSymbol(),i,"DUPLIKAT");
            getSaleManager()->print(document,getCopyOrOriginal(),getPrinter());

            if(!getView()->isDuplicate())
                options(document->getSymbol(),i,"KOPIA");
            else
                options(document->getSymbol(),i,"DUPLIKAT");
            for(int i=0;i<getView()->getSpinBox()->text().toInt();i++)
            {
                getSaleManager()->print(document,getCopyOrOriginal(),getPrinter());
            }
            setSaveToPdf(false);
        }
    }
    if(viewSignal!=0)
        printRelated(document->getRelatedDocuments());
}

void PrintSaleDocumentController::print(DocumentFK *document)
{
    setSymbol(document->getSymbol());
    setType(document->getDocumentType());
    int viewSignal=0;
    if(!getPrintReleated())
    {
        addDocToTable(document->getRelatedDocuments());
        viewSignal=getView()->exec();
    }

    if(viewSignal==1||getPrintReleated())
    {
        for(int i =0; i <getPrintAndSave();i++)
        {
            if(!getView()->isDuplicate())
                options(document->getSymbol(),i,"ORYGINAŁ");
            else
                options(document->getSymbol(),i,"DUPLIKAT");
            getSaleManager()->print(document,getCopyOrOriginal(),getPrinter());

            if(!getView()->isDuplicate())
                options(document->getSymbol(),i,"KOPIA");
            else
                options(document->getSymbol(),i,"DUPLIKAT");
            for(int i=0;i<getView()->getSpinBox()->text().toInt();i++)
            {
                getSaleManager()->print(document,getCopyOrOriginal(),getPrinter());
            }
            setSaveToPdf(false);

        }
    }
    if(viewSignal!=0)
    printRelated(document->getRelatedDocuments());
}

void PrintSaleDocumentController::printPreviewFile()
{
      if(getType().contains("FK"))
      {
          DocumentFK fk = getDocumentService()->getFK(getSymbol());
          if(!getView()->isDuplicate())
            getSaleManager()->print(&fk,"ORYGINAŁ",getPrinter());
          else
             getSaleManager()->print(&fk,"DUPLIKAT",getPrinter());

      }
      else if(getType().contains("ZAL")||getType().contains("RZL"))
      {
          DocumentZAL zal = getDocumentService()->getZAL(getSymbol());
          if(!getView()->isDuplicate())
             getSaleManager()->print(&zal,"ORYGINAŁ",getPrinter());
          else
             getSaleManager()->print(&zal,"DUPLIKAT",getPrinter());
      }
     else if(getType().contains("FV")||getType().contains("FMP")
               ||getType().contains("PA")||getType().contains("PI")
               ||getType().section("/",0,0)=="FM"||getType().contains("PRO"))
      {
         Invoice inv =  getDocumentService()->getInvoice(getSymbol());
         if(!getView()->isDuplicate())
            getSaleManager()->print(&inv,"ORYGINAŁ",getPrinter());
         else
            getSaleManager()->print(&inv,"DUPLIKAT",getPrinter());
      }

}

void PrintSaleDocumentController::createDirectories()
{
    QString documentsDirPath=getView()->getPath()->text();

    if(getSymbol().contains("FV")||getSymbol().contains("FK")||getSymbol().section('/',0,0)=="FM"||getSymbol().contains("FMP")||getSymbol().contains("PA")||getSymbol().contains("PI")||getSymbol().contains("PRO"))
    {
        if(!QDir().exists(documentsDirPath + "Dokumenty sprzedaży/"+getSymbol().section('/',0,0)))
            QDir().mkpath(documentsDirPath + "Dokumenty sprzedaży/"+getSymbol().section('/',0,0).toUpper());
    }
}

void PrintSaleDocumentController::setOutputFile()
{
    QString documentsDirPath=getView()->getPath()->text();

    QString dir = getSymbol().section('/',0,0).toUpper().append('/');
    QString symbolCopy = getSymbol();
    if(getSaveToPdf())
    {

      if(getSymbol().contains("FV")||getSymbol().contains("FK")||getSymbol().section('/',0,0)=="FM"||getSymbol().contains("FMP")||getSymbol().contains("PA")||getSymbol().contains("PI")||getSymbol().contains("PRO"))
          getPrinter()->setOutputFileName(documentsDirPath +"Dokumenty sprzedaży/"+dir+symbolCopy.replace('/','_')+"_"+getCopyOrOriginal().toLower()+".pdf");
     }
}
void PrintSaleDocumentController::printRelated(QVector<SimpleDocumentInfo> vectorDoc)
{
   /* setPrintReleated(true);
    for(int i=0; i<vectorDoc.size();i++)
    {
        if(vectorDoc[i].getSymbol().contains("FK") && getView()->getTable()->item(i,0)->checkState()==Qt::Checked)
        {
            DocumentFK fk = getDocumentService()->getFK(vectorDoc[i].getSymbol());
            this->print(&fk);
        }
        else if(vectorDoc[i].getSymbol().contains("WZ") && getView()->getTable()->item(i,0)->checkState()==Qt::Checked)
        {
            DocumentWZ wz = getDocumentService()->getWZ(vectorDoc[i].getSymbol());
            this->print(&wz);
        }
        else if(vectorDoc[i].getSymbol().contains("PZ") && getView()->getTable()->item(i,0)->checkState()==Qt::Checked)
        {
            DocumentPZ pz = getDocumentService()->getPZ(vectorDoc[i].getSymbol());
            this->print(&pz);
        }
        else if((vectorDoc[i].getType().contains("ZAL")||vectorDoc[i].getType().contains("RZL")) && getView()->getTable()->item(i,0)->checkState()==Qt::Checked)
        {
            DocumentZAL zal = getDocumentService()->getZAL(vectorDoc[i].getSymbol());
            this->print(&zal);
        }
        else if((vectorDoc[i].getSymbol().contains("RW")||vectorDoc[i].getSymbol().contains("PW")) && getView()->getTable()->item(i,0)->checkState()==Qt::Checked)
        {
            StoreDocument st = getDocumentService()->getStore(vectorDoc[i].getSymbol());
            this->print(&st);
        }
        else if((vectorDoc[i].getType().contains("FV")||vectorDoc[i].getType().contains("FMP")
                 ||vectorDoc[i].getSymbol().contains("PA")||vectorDoc[i].getSymbol().contains("PI")
                 ||vectorDoc[i].getSymbol().section("/",0,0)=="FM"||vectorDoc[i].getSymbol().contains("PRO"))
                && getView()->getTable()->item(i,0)->checkState()==Qt::Checked)
        {
            Invoice inv = getDocumentService()->getInvoice(vectorDoc[i].getSymbol());
            this->print(&inv);
        }

    }*/
}


PrintSaleDocumentManager* PrintSaleDocumentController::getSaleManager(){return saleManager;}
void PrintSaleDocumentController::setSaleManager(PrintSaleDocumentManager *saleManager){this->saleManager=saleManager;}
