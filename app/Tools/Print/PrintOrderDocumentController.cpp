#include "PrintOrderDocumentController.h"

PrintOrderDocumentController::PrintOrderDocumentController(QString symbol) : PrintDialogController(symbol)
{
     setOrderManager(new PrintOrderDocumentManager());
}

void PrintOrderDocumentController::print(Order *document)
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
            getOrderManager()->print(document,getCopyOrOriginal(),getPrinter());

            if(!getView()->isDuplicate())
                options(document->getSymbol(),i,"KOPIA");
            else
                options(document->getSymbol(),i,"DUPLIKAT");
            for(int i=0;i<getView()->getSpinBox()->text().toInt();i++)
            {
                getOrderManager()->print(document,getCopyOrOriginal(),getPrinter());
            }
            setSaveToPdf(false);

        }
    }
    if(viewSignal!=0)
    printRelated(document->getRelatedDocuments());
}
void PrintOrderDocumentController::printPreviewFile()
{
        Order order = getDocumentService()->getOrder(getSymbol());
        if(!getView()->isDuplicate())
          getOrderManager()->print(&order,"ORYGINAŁ",getPrinter());
        else
           getOrderManager()->print(&order,"DUPLIKAT",getPrinter());

}

void PrintOrderDocumentController::createDirectories()
{
    QString documentsDirPath=getView()->getPath()->text();

      if(!QDir().exists(documentsDirPath + "Dokumenty zamówień/"+getSymbol().section('/',0,0)))
      QDir().mkpath(documentsDirPath + "Dokumenty zamówień/"+getSymbol().section('/',0,0).toUpper());

}

void PrintOrderDocumentController::setOutputFile()
{
    QString documentsDirPath=getView()->getPath()->text();

    QString dir = getSymbol().section('/',0,0).toUpper().append('/');

    QString symbolCopy = getSymbol();
    if(getSaveToPdf())
    {
            getPrinter()->setOutputFileName(documentsDirPath +"Dokumenty zamówień/"+dir+symbolCopy.replace('/','_')+"_"+getCopyOrOriginal().toLower()+".pdf");
    }
}

void PrintOrderDocumentController::printRelated(QVector<SimpleDocumentInfo> vectorDoc)
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
PrintOrderDocumentManager* PrintOrderDocumentController::getOrderManager(){return orderManager;}
void PrintOrderDocumentController::setOrderManager(PrintOrderDocumentManager *orderManager){this->orderManager=orderManager;}
