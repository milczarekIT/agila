#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMenuBar>
#include <QStatusBar>
#include <QMainWindow>
#include <QStackedWidget>
#include "Main/MainTab.h"
#include "Main/MainMenu.h"
#include "Other/Application/Style.h"
#include "Tools/Updater/UpdateHelper.h"
#include "Tools/Archiver/ArchiverReminder.h"
#include "Main/MainStoreComboBoxController.h"
#include "Tools/Archiver/ArchiverAutoRemover.h",

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QTimer *idleTimer;
    QStatusBar *statusBar;
    QGridLayout *mainLayout;
    QWidget *window;
    QPalette palette;
    Button *buttonLogout;
    QLabel *loggedUser;
    QStackedWidget *centralElement;
    QStackedLayout *layout;
    QSpacerItem *verticalSpacer;
    MainTab *tab;
    MainMenuController *menu;
    MainStoreComboBoxController *storeComboBox;
    UpdateHelper *updateHelper;

    /**
      * Usuwa automatycznie stare backupy jeśli użytkownik tak ustawił
      */
    void initAutoRemovingOldBackups();
    void initMainInterface();
    void setTabOrders();
    void initConnections();
    void addTableViewsAsCentralElements();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void checkApplicationUpdates();
    bool isModuleWithTableView(ModuleManager::Module module);
    void initStartConf();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setMainWindowUserInfo();
    MainTab *getTab();
    void timerStart();
    void timerStop();
    QTimer *getIdleTimer();

protected:
    void closeEvent(QCloseEvent *event);

public slots:
    void show();
    void setCurrentTab(int index);
    void refreshView();
    void emitLogout();

signals:
    void logout();
};

#endif // MAINWINDOW_H
