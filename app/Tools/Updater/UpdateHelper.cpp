#include "UpdateHelper.h"

UpdateHelper::UpdateHelper()
{
}

void UpdateHelper::checkApplicationUpdates() {

    // rejestracja MediaType dla wielowątkowych sygnałow
    typedef UpdateInfo UpdateInfo;
    qRegisterMetaType<UpdateInfo>("UpdateInfo");

    updateChecker = new UpdateChecker();
    connect(updateChecker, SIGNAL(updateAvailable(UpdateInfo)), this, SLOT(showUpdateAvailableInfo(UpdateInfo)));
    updateChecker->start();

    QEventLoop *loop = new QEventLoop();
    QObject::connect(updateChecker, SIGNAL(finished()), loop, SLOT(quit()));
    loop->exec();

    delete updateChecker;
}

void UpdateHelper::showUpdatedSuccesfullInfo(UpdateInfo updateInfo) {

    MessageBox msg;
    msg.createInfoBox("Zaktualizowano do wersji <i>" + updateInfo.getNewVersionName() + "</i>. Zmiany będą widoczne przy ponownym uruchomieniu aplikacji");
}

void UpdateHelper::showUpdateAvailableInfo(UpdateInfo updateInfo) {

    MessageBox msg;
    int ret = msg.createQuestionBox("Dostępna jest nowa wersja oprogramowania: " + updateInfo.getNewVersionName() + ".",
                          "Czy chesz ją pobrać, a następnie zainstalować?");

    if(ret == MessageBox::YES)
    {
        this->updater = new Updater(updateInfo);
        connect(updater, SIGNAL(finishedSuccesufull(UpdateInfo)), this, SLOT(showUpdatedSuccesfullInfo(UpdateInfo)));
        updater->start();

        QEventLoop *loop = new QEventLoop();
        QObject::connect(updateChecker, SIGNAL(finished()), loop, SLOT(quit()));
        loop->exec();
    }
}

