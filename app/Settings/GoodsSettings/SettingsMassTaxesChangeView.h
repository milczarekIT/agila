#ifndef SETTINGSMASSTAXESCHANGEVIEW_H
#define SETTINGSMASSTAXESCHANGEVIEW_H

#include <QLabel>
#include <QWidget>
#include <QComboBox>
#include <QRadioButton>
#include "Components/Button.h"
#include "SettingsMassTaxesChangeController.h"
#include "Settings/SettingsAbstractItemView.h"
class SettingsMassTaxesChangeController;

class SettingsMassTaxesChangeView : public SettingsAbstractItemView
{
    Q_OBJECT
private:
    QRadioButton *radioNet;
    QRadioButton *radioGross;
    QLabel *label;
    QComboBox *actualTax;
    QComboBox *newTax;
    QComboBox *goodGroup;
    QComboBox *priceType;
    Button *pushSave;
    SettingsMassTaxesChangeController *controller;
    void initGraphicElements();
    void setGraphicSettings();
    void setInterfaceController();
    void fillPriceTypeBox();

public:
    explicit SettingsMassTaxesChangeView(SettingsMassTaxesChangeController *controller, QWidget *parent = 0);
    QRadioButton *getRadioNet();
    QRadioButton *getRadioGross();
    QLabel *getLabel();
    QComboBox *getActualTax();
    QComboBox *getNewTax();
    QComboBox *getGoodGroup();
    QComboBox *getPriceType();
    Button *getPushSave();

signals:

public slots:

};

#endif // SETTINGSMASSTAXESCHANGEVIEW_H
