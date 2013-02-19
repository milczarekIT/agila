#include "UpdateChecker.h"

UpdateChecker::UpdateChecker()
{
}

void UpdateChecker::run() {
    checkUpdate();
}

void UpdateChecker::checkUpdate() {
    QString applicationName = ApplicationManager::getInstance()->getApplicationName().remove(" ");

    /**
     * dokumentacja dla http://agila.bluebraces.com/service/checkUpdate/$appName/$versionCode
     *
     * @param $appName dozwolone wartości "AgilaFaktury", "AgilaS3" (bez spacji!)
     * @param $versionCode - aktualny numer wersji kodu
     * @return 'NONE' - niewłaściwa liczba argumentów
     * @return 'INCORRECT_APP_NAME' - niewłasciwa nazwa aplikacji
     * @return '{"newVersionCode":2,"newVersionName":"1.2","downloadLink":...}' - odpowiedz JSON
     */

    QStringList args; // kolejność ma znaczenie!
    args << applicationName << QVariant(ApplicationInfo::getVersionCode()).toString();

    HttpRequester *requester = new HttpRequester();
    try {
        QString response = requester->sendAgilaServiceRequest("checkUpdate", args);
        delete requester;

        if(response == "NONE") {
            emit noUpdateAvailable();
        }
        else if(response == "INCORRECT_APP_NAME") {
            //  "Błąd wywołania requestu! Błąd: 102";
        }
        else if(response.startsWith("{"))
        {
           // jest dostępna aktualizacja

            JsonObject *jObject = new JsonObject(response);

            UpdateInfo updateInfo;
            updateInfo.setNewVersionCode(jObject->getInt("newVersionCode"));
            updateInfo.setNewVersionName(jObject->getString("newVersionName"));
            updateInfo.setDownloadLink(jObject->getString("downloadLink"));
            delete jObject;

            emit updateAvailable(updateInfo);
        }

    } catch(NoHttpResponseException *e) {

        delete requester;
    }
}
