#ifndef SettingsPriceSelectionView_H
#define SettingsPriceSelectionView_H

#include <QDir>
#include <QLabel>
#include <QWidget>
#include <QRadioButton>
#include "Other/Application/ApplicationManager.h"
#include "SettingsPriceSelectionController.h"
#include "Settings/SettingsAbstractItemView.h"
class SettingsPriceSelectionController;

class SettingsPriceSelectionView : public SettingsAbstractItemView
{
    Q_OBJECT
private:
    void initGraphicElements();
    void setGraphicSettings();
    void setInterfaceController();
    SettingsPriceSelectionController *controller;
    QLabel *gross;
    QLabel *net;
    QRadioButton *radioGross;
    QRadioButton *radioNet;

public:
    explicit SettingsPriceSelectionView(SettingsPriceSelectionController *controller, QWidget *parent = 0);
    QRadioButton *getRadioGross();
    QRadioButton *getRadioNet();

};

#endif // SettingsPriceSelectionView_H
