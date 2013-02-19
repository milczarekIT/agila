#ifndef UPDATEHELPER_H
#define UPDATEHELPER_H

#include <QString>
#include <QProcess>
#include "UpdateChecker.h"
#include "Updater.h"

class UpdateHelper : public QObject
{
    Q_OBJECT

    UpdateChecker *updateChecker; // sprawdza i informuje o nowych dostępnych aktualizacjach
    Updater *updater; // pobiera i instaluje aktualizacje;
public:
    UpdateHelper();

    void checkApplicationUpdates();

private slots:
    void showUpdateAvailableInfo(UpdateInfo updateInfo);
    void showUpdatedSuccesfullInfo(UpdateInfo updateInfo);
};

#endif // UPDATEHELPER_H
