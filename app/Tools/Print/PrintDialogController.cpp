#include "PrintDialogController.h"
PrintDialogController::PrintDialogController(QString symbol,QWidget *parent)
{
    setSymbol(symbol);
    setPrinter(new QPrinter(QPrinter::HighResolution));
    setSettings(new QSettings());
    setDocumentService(new DocumentServices());
    setSaveToPdf(false);
    setPrintReleated(false);
    setPrintAndSave(1);
    setPreferences(new SettingsPreferencesService());
    setManager(new PrintManager());
    setView(new PrintDialogView(parent,this));
    directories();
    restoreDefaultPrintPreferences();
}

PrintDialogController::~PrintDialogController()
{
    setUserSaveToPdfDirectories();
    if(arePrintPreferencesChanged())
    setDefaultPrintPreferences();
    delete printer;
    delete settings;
    delete manager;
    delete view;
    delete docServ;
}

void PrintDialogController::initOptions()
{
    setOptions();
    if(getSaveToPdf())
    {
        createDirectories();
    }

}

void PrintDialogController::restoreDefaultPrintPreferences()
{
    getView()->getSpinBox()->setValue(preferences->getDefaultPrintNumberOfCopies());
    getView()->getBoxPrint()->setCurrentIndex(preferences->getDefaultPrintAction());
}

void PrintDialogController::setDefaultPrintPreferences()
{
    getPreferences()->setDefaultPrintNumberOfCopies(getView()->getSpinBox()->text().toInt());
    getPreferences()->setDefaultPrintAction(getView()->getBoxPrint()->currentIndex());
}

bool PrintDialogController::arePrintPreferencesChanged()
{
    if(getView()->getSpinBox()->text().toInt()!=preferences->getDefaultPrintNumberOfCopies()||
            getView()->getBoxPrint()->currentIndex()!=preferences->getDefaultPrintAction())
        return true;
    else
        return false;
}
void PrintDialogController::directories()
{
    if(getUserSaveToPdfDirectories().isEmpty())
    {
        getSettings()->beginGroup("PrintSettings");
        getSettings()->setValue("path", ApplicationManager::DIR_HOME_AGILA + QDir::separator());
        getSettings()->endGroup();
        getView()->getPath()->setText(ApplicationManager::DIR_HOME_AGILA + QDir::separator());
    }
    else
        getView()->getPath()->setText(getUserSaveToPdfDirectories());
}

void PrintDialogController::setUserSaveToPdfDirectories()
{
    if(getView()->ifSetAsDefualtPath()){
    getSettings()->beginGroup("PrintSettings");
    getSettings()->setValue("path", getView()->getPath()->text());
    getSettings()->endGroup();}
}

QString PrintDialogController::getUserSaveToPdfDirectories()
{
    getSettings()->beginGroup("PrintSettings");
    QString path = getSettings()->value("path").toString();
    getSettings()->endGroup();
    return path;
}

void PrintDialogController::setOptions()
{
    getPrinter()->setOutputFormat(QPrinter::NativeFormat);
    getPrinter()->setPageMargins(5,15,5,10,QPrinter::Millimeter);
     if(getView()->getBoxPrint()->currentIndex()==0){
         setSaveToPdf(true);
        setPrintAndSave(2);}
     else if(getView()->getBoxPrint()->currentIndex()==1)
          {  setSaveToPdf(false);
             setPrintAndSave(1);}
    else if(getView()->getBoxPrint()->currentIndex()==2)
         {  setSaveToPdf(true);
            setPrintAndSave(1);}
}

/*void PrintDialogController::setOutputFile()
{
    QString documentsDirPath=view->getPath()->text();

    QString dir = symbol.section('/',0,0).toUpper().append('/');
    QString symbolCopy = symbol;
    if(safeToPdf)
    {

      if(symbol.contains("FV")||symbol.contains("FK")||symbol.section('/',0,0)=="FM"||symbol.contains("FMP")||symbol.contains("PA")||symbol.contains("PI")||symbol.contains("PRO"))
          printer->setOutputFileName(documentsDirPath +"Dokumenty sprzedaży/"+dir+symbolCopy.replace('/','_')+"_"+copyOriginal.toLower()+".pdf");
      else if (symbol.contains("RR")||symbol.contains("FZ")||symbol.contains("NK")||symbolCopy.contains("FZK"))
          printer->setOutputFileName(documentsDirPath +"Dokumenty zakupu/"+dir+symbolCopy.replace('/','_')+"_"+copyOriginal.toLower()+".pdf");
      else if(symbol.contains("ZD")||symbol.contains("ZK"))
          printer->setOutputFileName(documentsDirPath +"Dokumenty zamówień/"+dir+symbolCopy.replace('/','_')+"_"+copyOriginal.toLower()+".pdf");
      else if(symbol.contains("RW")||symbol.contains("PW")||symbol.contains("WZ")||symbol.contains("PZ")||symbol.contains("MM"))
          printer->setOutputFileName(documentsDirPath +"Dokumenty magazynowe/"+dir+symbolCopy.replace('/','_')+"_"+copyOriginal.toLower()+".pdf");
      else if(symbol.contains("KP")||symbol.contains("KW"))
          printer->setOutputFileName(documentsDirPath +"Dokumenty kasowe/"+dir+symbolCopy.replace('/','_')+"_"+copyOriginal.toLower()+".pdf");
     }
}*/

void PrintDialogController::options(QString symbol,int print,QString copy)
{
    setCopyOrOriginal(copy);
    setSymbol(symbol);
    if(copy=="ORYGINAŁ"||copy=="DUPLIKAT")
    initOptions();
    setOutputFile();
    if(print) //usuniecie deafultowego miejsca zapisania powoduje przekierowanie na drukarke
    getPrinter()->setOutputFileName("");

}

void PrintDialogController::addDocToTable(QVector<SimpleDocumentInfo> vectorDoc)
{
    getView()->getTable()->setRowCount(vectorDoc.size());
    for(int i =0; i<vectorDoc.size();i++)
    {
    getView()->getTable()->setItem(i,0,new QTableWidgetItem(vectorDoc.value(i).getSymbol()));
    getView()->getTable()->item(i,0)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled|Qt::ItemIsUserCheckable);
    getView()->getTable()->item(i,0)->setCheckState(Qt::Unchecked);
    getView()->getTable()->setItem(i,1,new QTableWidgetItem(QVariant(vectorDoc.value(i).getDocumentDate()).toString()));
    getView()->getTable()->item(i,1)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    }

}

int PrintDialogController::show()
{
    return getView()->exec();
}

/*void PrintDialogController::createDirectories()
{
    QString documentsDirPath=view->getPath()->text();

    if(symbol.contains("FV")||symbol.contains("FK")||symbol.section('/',0,0)=="FM"||symbol.contains("FMP")||symbol.contains("PA")||symbol.contains("PI")||symbol.contains("PRO"))
    {
      if(!QDir().exists(documentsDirPath + "Dokumenty sprzedaży/"+symbol.section('/',0,0)))
      QDir().mkpath(documentsDirPath + "Dokumenty sprzedaży/"+symbol.section('/',0,0).toUpper());
    }
    else if (symbol.contains("RR")||symbol.contains("FZ")||symbol.contains("NK")||symbol.contains("FZK"))
    {
      if(!QDir().exists(documentsDirPath + "Dokumenty zakupu/"+symbol.section('/',0,0)))
      QDir().mkpath(documentsDirPath + "Dokumenty zakupu/"+symbol.section('/',0,0).toUpper());
    }
    else if(symbol.contains("ZD")||symbol.contains("ZK"))
    {
      if(!QDir().exists(documentsDirPath + "Dokumenty zamówień/"+symbol.section('/',0,0)))
      QDir().mkpath(documentsDirPath + "Dokumenty zamówień/"+symbol.section('/',0,0).toUpper());
    }
    else if(symbol.contains("RW")||symbol.contains("PW")||symbol.contains("WZ")||symbol.contains("PZ")||symbol.contains("MM"))
    {
      if(!QDir().exists(documentsDirPath + "Dokumenty magazynowe/"+symbol.section('/',0,0)))
      QDir().mkpath(documentsDirPath + "Dokumenty magazynowe/"+symbol.section('/',0,0).toUpper());
    }
    else if(symbol.contains("KP")||symbol.contains("KW"))
    {
    if(!QDir().exists(documentsDirPath+ "Dokumenty kasowe/"+symbol.section('/',0,0)))
    QDir().mkpath(documentsDirPath + "Dokumenty kasowe/"+symbol.section('/',0,0).toUpper());
    }
}*/

void PrintDialogController::printPreview()
{
    PrintPreviewDialog *preview = new PrintPreviewDialog(getPrinter());
    connect(preview->getPreview(),SIGNAL(paintRequested(QPrinter*)),this,SLOT(printPreviewFile()));
    preview->show();
    delete preview;
}

void PrintDialogController::browsePath()
{
    fDialog = new QFileDialog();
    QString path = fDialog->getExistingDirectory();
    if(!path.isEmpty())
    {
    getView()->getPath()->setText(path+"/");
    }
}

void PrintDialogController::printerChooser(QString name)
{
    getPrinter()->setPrinterName(name);
    getPrinter()->setPrinterSelectionOption(name);
}

QString PrintDialogController::getSymbol(){return symbol;}
void PrintDialogController::setSymbol(QString symbol){this->symbol=symbol;}
QString PrintDialogController::getType(){return type;}
void PrintDialogController::setType(QString type){this->type=type;}
bool PrintDialogController::getPrintReleated(){return printReleatedDoc;}
void PrintDialogController::setPrintReleated(bool printReleated){this->printReleatedDoc=printReleated;}
PrintDialogView* PrintDialogController::getView(){return view;}
void PrintDialogController::setView(PrintDialogView* view){this->view=view;}
int PrintDialogController::getPrintAndSave(){return printAndSave;}
void PrintDialogController::setPrintAndSave(int printAndSave){this->printAndSave=printAndSave;}
PrintManager* PrintDialogController::getManager(){return manager;}
void PrintDialogController::setManager(PrintManager* manager){this->manager=manager;}
QString PrintDialogController::getCopyOrOriginal(){return copyOriginal;}
void PrintDialogController::setCopyOrOriginal(QString copyOrOriginal){this->copyOriginal=copyOrOriginal;}
QPrinter* PrintDialogController::getPrinter(){return printer;}
void PrintDialogController::setPrinter(QPrinter* printer){this->printer=printer;}
bool PrintDialogController::getSaveToPdf(){return saveToPdf;}
void PrintDialogController::setSaveToPdf(bool saveToPdf){this->saveToPdf=saveToPdf;}
DocumentServices* PrintDialogController::getDocumentService(){return docServ;}
void PrintDialogController::setDocumentService(DocumentServices* docService){this->docServ=docService;}
SettingsPreferencesService *PrintDialogController::getPreferences(){return preferences;}
void PrintDialogController::setPreferences(SettingsPreferencesService* preferences){this->preferences=preferences;}
QSettings *PrintDialogController::getSettings(){return settings;}
void PrintDialogController::setSettings(QSettings* settings){this->settings=settings;}
