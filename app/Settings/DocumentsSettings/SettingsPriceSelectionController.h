#ifndef SettingsPriceSelectionController_H
#define SettingsPriceSelectionController_H

#include <QObject>
#include "SettingsPriceSelectionView.h"
#include "Settings/SettingsAbstractItemController.h"
#include "Other/Preferences/SettingsPreferencesService.h"
class SettingsPriceSelectionView;

class SettingsPriceSelectionController : public SettingsAbstractItemController
{
    Q_OBJECT
private:
    SettingsPriceSelectionView *view;
    SettingsPreferencesService *preferences;
public:
    explicit SettingsPriceSelectionController(QObject *parent = 0);
    SettingsPriceSelectionView *getView();

public slots:
    void changeDefault();

};

#endif // SettingsPriceSelectionController_H
