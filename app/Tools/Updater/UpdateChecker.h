#ifndef UPDATECHECKER_H
#define UPDATECHECKER_H

#include <QThread>
#include <QDebug>
#include "Other/Application/ApplicationManager.h"
#include "Other/Application/ApplicationInfo.h"
#include "Other/Network/HttpRequester.h"
#include "Other/Network/JsonObject.h"
#include "Tools/LicenseChecker/LicenseChecker.h"
#include "UpdateInfo.h"

class UpdateChecker : public QThread
{
    Q_OBJECT

protected:
    void run();

private:
    void checkUpdate();

public:
    UpdateChecker();

signals:
    void updateAvailable(UpdateInfo updateInfo);
    void noUpdateAvailable();
};

#endif // UPDATECHECKER_H
