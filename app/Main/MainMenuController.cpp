#include "MainMenuController.h"
#include <QProcess>
#include <QLibraryInfo>
#include <QMessageBox>
#include <QTextStream>
#include "Components/ProgressBarDialog.h"

MainMenuController::MainMenuController()
{
    view = new MainMenu(this);
}

void MainMenuController::showHelp()
{
    helpDialog = new HelpDialogView();
    helpDialog->exec();

    /*QProcess *process = new QProcess(this);
    QString app = QLibraryInfo::location(QLibraryInfo::BinariesPath)
        + QLatin1String("/assistant");

    process->start(app, QStringList() << QLatin1String("-enableRemoteControl"));
    if (!process->waitForStarted()) {
        return;
    }*/
    delete helpDialog;

}

MainMenu *MainMenuController::getView()
{
    return view;
}

