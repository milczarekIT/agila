#include "SettingsAbstractItemController.h"

SettingsAbstractItemController::SettingsAbstractItemController(QObject *parent) :
    QObject(parent)
{
}

int SettingsAbstractItemController::getButtonStatus(){return buttonStatus;}
void SettingsAbstractItemController::setButtonStatus(int buttonStatus){ this->buttonStatus = buttonStatus; }
