#ifndef SETTINGSUSERCONTROLLER_H
#define SETTINGSUSERCONTROLLER_H

#include <QObject>
#include "User/UserModel.h"
#include "SettingsUserView.h"
#include "Other/Application/ApplicationManager.h"
#include "Settings/SettingsAbstractItemController.h"
class SettingsUserView;

class SettingsUserController : public SettingsAbstractItemController
{
    Q_OBJECT
private:
    SettingsUserView *view;
    UserModel *model;
    User *user;
    QString pass;
    void setModel(QString login = "");
    void setData(User *u);
    QString createHashCode(QString password);
    bool checkDesireToEditPassword();
    bool checkFillForEdit();
    bool checkFillForAdd();
    bool passwordsAreCorrect();
    bool checkCorrectnessOfNewPassword();
    void fillBox(QComboBox *box,QVector<User> values);
    void saveAddition(User *u);
    void saveChanges(User *u);


public:
    explicit SettingsUserController(QObject *parent = 0);
    ~SettingsUserController();
    SettingsUserView *getView();

public slots:
    void save();
    void showSignsInPasswordFields(bool state);
    void addUser();
    void showUserData(int index);
    void removeUser();
    void showAdminComponents(bool show);
    void updateAfterLogging(User u);
};

#endif // SETTINGSUSERCONTROLLER_H
