#include "SettingsTransportController.h"

SettingsTransportController::SettingsTransportController(QWidget *parent) :
        SettingsAbstractItemController(parent)
{
    this->view = new SettingsTransportView(this,parent);
}

SettingsTransportController::~SettingsTransportController()
{
}

void SettingsTransportController::showTransports()
{
}

void SettingsTransportController::addTransport()
{
}

 void SettingsTransportController::editTransport()
 {
 }

 void SettingsTransportController::deleteTransport()
 {
 }

 void SettingsTransportController::saveTransport()
 {
 }

 SettingsTransportView * SettingsTransportController::getView() {return view;}

