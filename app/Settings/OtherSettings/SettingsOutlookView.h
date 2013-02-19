#ifndef SETTINGSOUTLOOKVIEW_H
#define SETTINGSOUTLOOKVIEW_H

#include <QDir>
#include <QLabel>
#include <QWidget>
#include <QRadioButton>
#include "Components/Button.h"
#include "SettingsOutlookController.h"
#include "Settings/SettingsAbstractItemView.h"
#include "Other/Application/ApplicationManager.h"
class SettingsOutlookController;

class SettingsOutlookView : public SettingsAbstractItemView
{
    Q_OBJECT
private:
    void initGraphicElements();
    void setGraphicSettings();
    void setInterfaceController();
    SettingsOutlookController *controller;
    QLabel *grey;
    QLabel *blue;
    QRadioButton *radioGrey;
    QRadioButton *radioBlue;
    QRadioButton *radioStandard;
    Button *save;

public:
    explicit SettingsOutlookView(SettingsOutlookController *controller, QWidget *parent = 0);
    void setPhoto(QString path, QLabel *label);
    QRadioButton *getRadioGrey();
    QRadioButton *getRadioBlue();
    QRadioButton *getRadioStandard();

signals:

public slots:

};

#endif // SETTINGSOUTLOOKVIEW_H
