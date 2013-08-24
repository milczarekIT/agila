#ifndef LOGGINGSYSTEMVIEW_H
#define LOGGINGSYSTEMVIEW_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QDialogButtonBox>
#include "User/User.h"
#include "Components/MessageBox.h"
#include "User/LoggingSystemController.h"
class LoggingSystemController;

class LoggingSystemView : public QDialog
{
    Q_OBJECT
private:
    void initComponents();
    void initConnections();

    QLabel *logo;
    QGridLayout *layout;
    QGridLayout *layoutLog;
    QLineEdit* lineLogin;
    QLineEdit* linePassword;
    QLabel *infoAboutUserAccess;
    QDialogButtonBox *buttonBox;
    LoggingSystemController *controller;

public:
    LoggingSystemView(LoggingSystemController *controller);
    ~LoggingSystemView();
    QString getLogin();
    QString getPassword();
    QLabel *getInfoAboutUserAccess();
    void showWrongLogin();
    void showWrongPassword();
    void emitLoggingSignal(User *u);

signals:
    void logged(User *u);
};

#endif // LOGGINGSYSTEMVIEW_H
