#include "SettingsOutlookController.h"

SettingsOutlookController::SettingsOutlookController(QObject *parent) :
    SettingsAbstractItemController(parent)
{
    view = new SettingsOutlookView(this);
    signProperBox();
}

void SettingsOutlookController::changeStyleSheet() {
    if(view->getRadioGrey()->isChecked())
        Style::getInstance()->changeApplicationStyle(Style::GREY);
    else if (view->getRadioBlue()->isChecked())
        Style::getInstance()->changeApplicationStyle(Style::BLUE);
    else if (view->getRadioStandard()->isChecked())
        Style::getInstance()->changeApplicationStyle(Style::STANDARD);

    MessageBox *mb = new MessageBox();
    mb->createInfoBox("W celu dokonania zmian wyglądu należy ponownie uruchomić program");
    signProperBox();

    delete mb;
}

void SettingsOutlookController::signProperBox() {
    if(Style::getInstance()->isBlueStyleSheet())
        view->getRadioBlue()->setChecked(true);
    else if (Style::getInstance()->isGreyStyleSheet())
        view->getRadioGrey()->setChecked(true);
    else if (Style::getInstance()->isStandardStyleSheet())
        view->getRadioStandard()->setChecked(true);
}

QString SettingsOutlookController::getStyleSheetPath() {
    return Style::getInstance()->getPath();
}

SettingsOutlookView *SettingsOutlookController::getView() {return view;}
