#include "SettingsPriceSelectionController.h"

SettingsPriceSelectionController::SettingsPriceSelectionController(QObject *parent) :
    SettingsAbstractItemController(parent)
{
    view = new SettingsPriceSelectionView(this);
    preferences = new SettingsPreferencesService();
    if(preferences->getPriceConversion())
        view->getRadioGross()->setChecked(true);
    else
        view->getRadioNet()->setChecked(true);
}

SettingsPriceSelectionView *SettingsPriceSelectionController::getView() {return view;}

void SettingsPriceSelectionController::changeDefault()
{
    if(view->getRadioNet()->isChecked())
        preferences->setPriceConversion(0);
    else
        preferences->setPriceConversion(1);
}
