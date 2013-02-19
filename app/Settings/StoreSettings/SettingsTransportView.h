#ifndef SETTINGSTRANSPORTVIEW_H
#define SETTINGSTRANSPORTVIEW_H

#include <QLabel>
#include <QWidget>
#include <QString>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include "Components/Button.h"
#include "Database/Database.h"
#include "Settings/SettingsAbstractItemView.h"
#include "SettingsTransportController.h"
class SettingsTransportController;

/**
  @author Janiu
  Klasa widgeta zawierającego elementy ustawień cech towarowych
  */
class SettingsTransportView : public SettingsAbstractItemView
{
    Q_OBJECT
private:
    SettingsTransportController *controller;
    QLineEdit *lineName;
    QComboBox * boxTransports;
    Button *pushSave;
    Button *pushEdit;
    Button *pushNew;
    Button *pushDelete;

public:
    QLineEdit *getLineName();
    QComboBox *getBoxTransports();
    Button *getPushSave();
    Button *getPushEdit();
    Button *getPushNew();
    Button *getPushDelete();
    int getButtonStatus();
    void setButtonStatus(int statusButton);
    explicit SettingsTransportView(SettingsTransportController *controller,QWidget *parent = 0);
    ~SettingsTransportView();
    void initGraphicElements();
    void setGraphicSettings();
    void setInterfaceController();
};

#endif // SETTINGSTRANSPORTVIEW_H
