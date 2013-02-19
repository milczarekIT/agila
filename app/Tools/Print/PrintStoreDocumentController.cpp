#include "PrintStoreDocumentController.h"

PrintStoreDocumentController::PrintStoreDocumentController(QString symbol) : PrintDialogController(symbol)
{
    setStoreManager(new PrintStoreDocumentManager());
}

void PrintStoreDocumentController::print(StoreDocument* document)
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
            getStoreManager()->print(document,getCopyOrOriginal(),getPrinter());

            if(!getView()->isDuplicate())
                options(document->getSymbol(),i,"KOPIA");
            else
                options(document->getSymbol(),i,"DUPLIKAT");
            for(int i=0;i<getView()->getSpinBox()->text().toInt();i++)
            {
                getStoreManager()->print(document,getCopyOrOriginal(),getPrinter());
            }
            setSaveToPdf(false);
        }
    }
    if(viewSignal!=0)
        printRelated(document->getRelatedDocuments());
}

void PrintStoreDocumentController::print(DocumentWZ *document)
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
            getStoreManager()->print(document,getCopyOrOriginal(),getPrinter());

            if(!getView()->isDuplicate())
                options(document->getSymbol(),i,"KOPIA");
            else
                options(document->getSymbol(),i,"DUPLIKAT");
            for(int i=0;i<getView()->getSpinBox()->text().toInt();i++)
            {
                getStoreManager()->print(document,getCopyOrOriginal(),getPrinter());
            }
            setSaveToPdf(false);
        }
    }
    if(viewSignal!=0)
        printRelated(document->getRelatedDocuments());
}

void PrintStoreDocumentController::print(DocumentPZ *document)
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
            getStoreManager()->print(document,getCopyOrOriginal(),getPrinter());

            if(!getView()->isDuplicate())
                options(document->getSymbol(),i,"KOPIA");
            else
                options(document->getSymbol(),i,"DUPLIKAT");
            for(int i=0;i<getView()->getSpinBox()->text().toInt();i++)
            {
                getStoreManager()->print(document,getCopyOrOriginal(),getPrinter());
            }
            setSaveToPdf(false);
        }
    }
    if(viewSignal!=0)
        printRelated(document->getRelatedDocuments());
}

void PrintStoreDocumentController::printPreviewFile()
{
      if(getType().contains("WZ"))
      {
          DocumentWZ wz = getDocumentService()->getWZ(getSymbol());
          if(!getView()->isDuplicate())
             getStoreManager()->print(&wz,"ORYGINAŁ",getPrinter());
          else
             getStoreManager()->print(&wz,"DUPLIKAT",getPrinter());
      }
      else if(getType().contains("PZ"))
      {
          DocumentPZ pz = getDocumentService()->getPZ(getSymbol());
          if(!getView()->isDuplicate())
             getStoreManager()->print(&pz,"ORYGINAŁ",getPrinter());
          else
             getStoreManager()->print(&pz,"DUPLIKAT",getPrinter());
      }
      else if(getType().contains("RW")||getType().contains("PW"))
      {
          StoreDocument st = getDocumentService()->getStore(getSymbol());
          if(!getView()->isDuplicate())
             getStoreManager()->print(&st,"ORYGINAŁ",getPrinter());
          else
             getStoreManager()->print(&st,"DUPLIKAT",getPrinter());
      }
}

void PrintStoreDocumentController::createDirectories()
{
    QString documentsDirPath=getView()->getPath()->text();

    if(getSymbol().contains("RW")||getSymbol().contains("PW")||getSymbol().contains("WZ")||getSymbol().contains("PZ")||getSymbol().contains("MM"))
    {
        if(!QDir().exists(documentsDirPath + "Dokumenty magazynowe/"+getSymbol().section('/',0,0)))
            QDir().mkpath(documentsDirPath + "Dokumenty magazynowe/"+getSymbol().section('/',0,0).toUpper());
    }
}

void PrintStoreDocumentController::setOutputFile()
{
    QString documentsDirPath=getView()->getPath()->text();

    QString dir = getSymbol().section('/',0,0).toUpper().append('/');
    QString symbolCopy = getSymbol();
    if(getSaveToPdf())
    {
        if(getSymbol().contains("RW")||getSymbol().contains("PW")||getSymbol().contains("WZ")||getSymbol().contains("PZ")||getSymbol().contains("MM"))
            getPrinter()->setOutputFileName(documentsDirPath +"Dokumenty magazynowe/"+dir+symbolCopy.replace('/','_')+"_"+getCopyOrOriginal().toLower()+".pdf");
    }
}

void PrintStoreDocumentController::printRelated(QVector<SimpleDocumentInfo> vectorDoc)
{
    /*setPrintReleated(true);
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

PrintStoreDocumentManager* PrintStoreDocumentController::getStoreManager(){return storeManager;}
void PrintStoreDocumentController::setStoreManager(PrintStoreDocumentManager *storeManager){this->storeManager=storeManager;}

