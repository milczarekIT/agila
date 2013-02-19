#include "SettingsDocumentTextController.h"

SettingsDocumentTextController::SettingsDocumentTextController(QWidget *parent) :
        SettingsAbstractItemController(parent)
{
    this->view = new SettingsDocumentTextView(this,parent);
    documentInfoModel = new DocumentInfoModel();

    setModel();
    view->setTableSettings();
    view->setIsEdited(true);
}

SettingsDocumentTextController::~SettingsDocumentTextController()
{
    delete documentInfoModel;
}

void SettingsDocumentTextController::setModel()
{
    updateTableByModules();
}

void SettingsDocumentTextController::updateTableByModules(){

    QVector<DocumentInfo> documentInfos;

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Sale))
    {
        foreach(DocumentInfo info,this->documentInfoModel->getDocumentsInfo("SALE"))
            documentInfos.push_back(info);
    }
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Purchase))
    {
        foreach(DocumentInfo info,this->documentInfoModel->getDocumentsInfo("PURCHASE"))
            documentInfos.push_back(info);
    }
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Cash))
    {
        foreach(DocumentInfo info,this->documentInfoModel->getDocumentsInfo("CASH"))
            documentInfos.push_back(info);
    }
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Order))
    {
        foreach(DocumentInfo info,this->documentInfoModel->getDocumentsInfo("ORDER"))
            documentInfos.push_back(info);
    }
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
    {
        foreach(DocumentInfo info,this->documentInfoModel->getDocumentsInfo("STORE"))
            documentInfos.push_back(info);
    }


    view->setDocumentsInfo(documentInfos);
    updateTable();
}

void SettingsDocumentTextController::updateTable()
{
    //view->setDocumentsInfo(this->documentInfoModel->getDocumentsInfo());
    view->getTableDTextes()->setColumnCount(2);
    view->getTableDTextes()->setRowCount(view->getDocumentsInfo().size());
    for(int i=0;i<view->getDocumentsInfo().size();i++) view->createItem(i);
}

void SettingsDocumentTextController::editText()
{
    int row = view->getTableDTextes()->currentRow();
    QString documentType = view->getDocumentsInfo()[row].getType();
    QString afterText = view->getTableDTextes()->item(row,1)->text();
    this->documentInfoModel->editAfterText(documentType, afterText);
    view->emitChangesWereMade();
}

void SettingsDocumentTextController::acceptAction()
{
    if (view->getIsEdited())
    {
        if (view->getMessageBox()->createQuestionBox("Edycja tekstu dla wybranego dokumentu !") == 2)
        {
            view->setIsEdited(true);
            editText();
        }
        else
        {
            view->setIsEdited(false);
            int row = view->getTableDTextes()->currentIndex().row();
            view->getTableDTextes()->currentItem()->setText(view->getDocumentsInfo()[row].getAfterText());
        }
     }
    else view->setIsEdited(true);
}

SettingsDocumentTextView *SettingsDocumentTextController::getView() {return view;}
DocumentInfoModel *SettingsDocumentTextController::getModel() { return documentInfoModel; }
