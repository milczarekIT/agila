#include "SettingsPanelController.h"

SettingsPanelController::SettingsPanelController(QWidget *parent)
{
    this->view = new SettingsPanelView(this,parent);
    initModularity();
}

void SettingsPanelController::getSettingsModel()
{
    view->getTabVAT()->setModel();
    view->getTabUnits()->setModel();
    view->getTabGoodGroups()->setModel();
    view->getTabFeatures()->setModel();
    view->getTabMassTaxesChange()->setModel();
    view->getTabConGroups()->setModel();
    view->getTabDocumentNumbering()->setModel();
    view->getTabMOP()->setModel();
    view->getTabDocumentText()->setModel();
    view->getTabDefDocPlace()->setModel();
    view->getTabOwner()->insertOwnerData1();
    // nie wiem jak z uzytkownikami, i magazynami
    initModularity();
}

void SettingsPanelController::demo(int i)
{
    if (i == 3)
    {
        QMessageBox *box = new QMessageBox();
        QMessageBox::information(this,QCoreApplication::applicationName(), "Niedostępne w wersji demonstracyjnej",QMessageBox::Ok);
        delete box;
    }
}

SettingsPanelView *SettingsPanelController::getView()
{
    return this->view;
}

//modułowość

void SettingsPanelController::initModularity(){

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
        view->getList()->item(3)->setHidden(false);
    else
        view->getList()->item(3)->setHidden(true);
}

