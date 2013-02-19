#include "Updater.h"

Updater::Updater(UpdateInfo updateInfo)
{
    this->updateInfo = updateInfo;
}

void Updater::run() {
    downloadUpdate();
    executeUpdate();

    emit finishedSuccesufull(updateInfo);
}

void Updater::downloadUpdate()
{
    HttpRequester *requester = new HttpRequester();
    updateFile = requester->downloadFile(updateInfo.getDownloadLink());
    delete requester;
}

void Updater::executeUpdate()
{
    QString fileName = updateFile->fileName();
    QString extension = QFileInfo(fileName).suffix();
    if(extension == "sh")
    {
        ApplicationInfo appInfo;

        QProcess *process = new QProcess();
        QStringList processArguments;
        processArguments << fileName << appInfo.getApplicationPath();

        process->start("bash", processArguments);
        while(process->waitForFinished(-1) == false)
        {
            QCoreApplication::processEvents();
        }
    }
}
