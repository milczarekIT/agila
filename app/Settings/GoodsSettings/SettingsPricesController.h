#ifndef SETTINGSPRICESCONTROLLER_H
#define SETTINGSPRICESCONTROLLER_H
#include <QVariant>
#include "Settings/SettingsAbstractItemController.h"
#include "Settings/GoodsSettings/SettingsPricesView.h"
#include "Other/Preferences/SettingsPreferencesService.h"
class SettingsPricesView;

class SettingsPricesController : public SettingsAbstractItemController
{
    Q_OBJECT

public:
    SettingsPricesController(QWidget *parent= 0);
    ~SettingsPricesController();
    SettingsPricesView* getView();

private:
    SettingsPricesView* view;
    SettingsPreferencesService * settingsService;
    void restoreSettings();

public slots:

    void saveSettings();
};

#endif // SETTINGSPRICESCONTROLLER_H
