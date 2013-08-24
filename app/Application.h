#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QDialog>
#include "MainWindow.h"
#include "Other/Owner/Owner.h"
#include "Other/Application/Style.h"
#include "Components/ProgressBarDialog.h"
#include "Other/Application/ArgumentsAnalyzer.h"

class Application : public QApplication
{
    Q_OBJECT

private:
    OwnerService *owner;
    MainWindow *mainWindow;
    LoggingSystemController* logger;

    void initMainWindow();
    void showMainWindow();
    int initLoginWindow();
    void login();
    void checkOwner();
    void setAppInformation();
    int run();

public:
    explicit Application(int argc, char *argv[]);
    ~Application();
    int initApplication(int argc, char *argv[]);
    
signals:
    
public slots:
    void logout();
    
};

#endif // APPLICATION_H
