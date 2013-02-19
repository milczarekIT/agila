#ifndef SETTINGSPRINTCONTROLLER_H
#define SETTINGSPRINTCONTROLLER_H

#include <QObject>
#include "SettingsPrintView.h"
#include "Settings/SettingsAbstractItemController.h"
class SettingsPrintView;

class SettingsPrintController : public SettingsAbstractItemController
{
    Q_OBJECT
private:
    SettingsPrintView *view;
public:
    explicit SettingsPrintController(QObject *parent = 0);
    SettingsPrintView *getView();
signals:

public slots:

};

#endif // SETTINGSPRINTCONTROLLER_H
