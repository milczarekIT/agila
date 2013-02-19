#ifndef SETTINGSPRINTVIEW_H
#define SETTINGSPRINTVIEW_H

#include <QLabel>
#include <QWidget>
#include "SettingsPrintController.h"
#include "Settings/SettingsAbstractItemView.h"
class SettingsPrintController;

class SettingsPrintView : public SettingsAbstractItemView
{
    Q_OBJECT
private:
    void initGraphicElements();
    void setGraphicSettings();
    void setInterfaceController();
    SettingsPrintController *controller;

public:
    explicit SettingsPrintView(SettingsPrintController *controller, QWidget *parent = 0);

signals:

public slots:

};

#endif // SETTINGSPRINTVIEW_H
