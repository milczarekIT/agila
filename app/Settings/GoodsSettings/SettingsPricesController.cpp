#include "SettingsPricesController.h"

SettingsPricesController::SettingsPricesController(QWidget *parent) :
    SettingsAbstractItemController(parent)
{
    this->view = new SettingsPricesView(this,parent);
    this->settingsService = new SettingsPreferencesService();
    restoreSettings();
}

SettingsPricesView* SettingsPricesController::getView()
{
    return this->view;
}
SettingsPricesController::~SettingsPricesController()
{
    delete settingsService;
}
void SettingsPricesController::restoreSettings()
{
    view->getLineMarginaA()->setText(QString::number(settingsService->getDefaultGoodsMargin(), ',', 2).replace(".", ","));
    view->getLineDiscountB()->setText(QString::number(settingsService->getDefaultGoodsDiscountB(), ',', 2).replace(".", ","));
    view->getLineDiscountC()->setText(QString::number(settingsService->getDefaultGoodsDiscountC(), ',', 2).replace(".", ","));
}

void SettingsPricesController::saveSettings()
{
    settingsService->setDefaultGoodsMargin(view->getLineMarginaA()->text().toDouble());
    settingsService->setDefaultGoodsDiscountB(view->getLineDiscountB()->text().toDouble());
    settingsService->setDefaultGoodsDiscountC(view->getLineDiscountC()->text().toDouble());
}
