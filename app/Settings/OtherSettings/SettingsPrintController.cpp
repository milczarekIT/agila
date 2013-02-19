#include "SettingsPrintController.h"

SettingsPrintController::SettingsPrintController(QObject *parent) :
    SettingsAbstractItemController(parent)
{
    view = new SettingsPrintView(this);
}

SettingsPrintView *SettingsPrintController::getView() {return view;}
