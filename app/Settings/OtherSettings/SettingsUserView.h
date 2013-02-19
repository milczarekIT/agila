#ifndef SETTINGSUSERVIEW_H
#define SETTINGSUSERVIEW_H

#include <QLabel>
#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>
#include "Components/Button.h"
#include "SettingsUserController.h"
#include "Settings/SettingsAbstractItemView.h"
class SettingsUserController;

class SettingsUserView : public SettingsAbstractItemView
{
    Q_OBJECT
private:
    QLineEdit *lineLogin;
    QLineEdit *lineActualPassword;
    QLineEdit *lineNewPassword;
    QLineEdit *lineReplyNewPassword;
    QLineEdit *lineName;
    QLineEdit *lineType;
    QCheckBox *showSigns;
    QComboBox *boxUsers;
    QComboBox *boxKindsOfAccount;
    QLabel *label[3];
    Button *pushSave;
    Button *pushAdd;
    Button *pushDelete;

    void initGraphicElements();
    void setGraphicSettings();
    void setInterfaceController();
    SettingsUserController *controller;

public:
    explicit SettingsUserView(SettingsUserController *controller, QWidget *parent = 0);
    QLineEdit *getLineLogin();
    QLineEdit *getLineName();
    QLineEdit *getLineActualPassword();
    QLineEdit *getLineNewPassword();
    QLineEdit *getLineReplyNewPassword();
    QCheckBox *getShowSigns();
    Button *getPushAdd();
    Button *getPushDelete();
    QComboBox *getBoxUsers();
    QComboBox *getBoxKindsOfAccount();
    QLabel **getLabel();

signals:

public slots:

};

#endif // SETTINGSUSERVIEW_H
