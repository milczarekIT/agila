#ifndef SETTINGSOUTLOOKCONTROLLER_H
#define SETTINGSOUTLOOKCONTROLLER_H

#include <QObject>
#include "SettingsOutlookView.h"
#include "Other/Application/Style.h"
#include "Settings/SettingsAbstractItemController.h"
class SettingsOutlookView;

class SettingsOutlookController : public SettingsAbstractItemController
{
    Q_OBJECT

private:
    SettingsOutlookView *view;

public:
    explicit SettingsOutlookController(QObject *parent = 0);
    SettingsOutlookView *getView();
    QString getStyleSheetPath();

public slots:
    void changeStyleSheet();
    void signProperBox();

};

#endif // SETTINGSOUTLOOKCONTROLLER_H
