#ifndef UPDATER_H
#define UPDATER_H

#include <QThread>
#include <QDebug>
#include <QFileInfo>
#include <QProcess>
#include <QCoreApplication>
#include "UpdateInfo.h"
#include "Other/Network/HttpRequester.h"
#include "Other/Application/ApplicationInfo.h"

/**
  * Klasa odpowiedzialna za pobieranie i instalowanie aktualizacji
  * @author Bartosz Milczarek
  */
class Updater : public QThread
{
    Q_OBJECT

    UpdateInfo updateInfo;
    QFile *updateFile;

protected:
    void run();

public:
    Updater(UpdateInfo updateInfo);

    void downloadUpdate();
    void executeUpdate();

signals:
    void finishedSuccesufull(UpdateInfo updateInfo);
};

#endif // UPDATER_H
