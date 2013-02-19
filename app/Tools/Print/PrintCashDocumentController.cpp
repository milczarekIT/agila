#include "PrintCashDocumentController.h"

PrintCashDocumentController::PrintCashDocumentController(QString symbol) : PrintDialogController(symbol)
{
}

void PrintCashDocumentController::printPreviewFile()
{


}

void PrintCashDocumentController::createDirectories()
{
    QString documentsDirPath=getView()->getPath()->text();

    if(getSymbol().contains("KP")||getSymbol().contains("KW"))
    {
        if(!QDir().exists(documentsDirPath+ "Dokumenty kasowe/"+getSymbol().section('/',0,0)))
        QDir().mkpath(documentsDirPath + "Dokumenty kasowe/"+getSymbol().section('/',0,0).toUpper());
    }
}

void PrintCashDocumentController::setOutputFile()
{
    QString documentsDirPath=getView()->getPath()->text();

    QString dir = getSymbol().section('/',0,0).toUpper().append('/');
    QString symbolCopy = getSymbol();
    if(getSaveToPdf())
    {
         if(getSymbol().contains("KP")||getSymbol().contains("KW"))
            getPrinter()->setOutputFileName(documentsDirPath +"Dokumenty kasowe/"+dir+symbolCopy.replace('/','_')+"_"+getCopyOrOriginal().toLower()+".pdf");
     }
}

void PrintCashDocumentController::printRelated(QVector<SimpleDocumentInfo> vectorDoc)
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
