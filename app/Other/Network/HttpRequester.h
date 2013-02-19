#ifndef HTTPREQUESTER_H
#define HTTPREQUESTER_H

#include <QObject>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QEventLoop>
#include <QTimer>
#include <QStringList>
#include <QFile>
#include <QDir>
#include "Other/Exceptions/NoHttpResponseException.h"

/**
  * Klasa odpowiedzialna za wysyłanie HttpRequestów oraz pobieranie odpowiedzi od zdalnego hosta
  */
class HttpRequester : public QObject
{
    Q_OBJECT

    QNetworkAccessManager *networkManager;
    QNetworkReply *reply;
    QEventLoop *loop;
public:
    HttpRequester();
    ~HttpRequester();

    /**
      * Wysyła requesta do http://agila.bluebraces.com/service/$serviceName/$arg.at(0)/$arg.at(1)...
      * @returns odpowiedź service'u jako string
      */
    QString sendAgilaServiceRequest(QString serviceName, QStringList args); // throws NoHttpResponseException
    QFile *downloadFile(QString fileUrl);

    const static QString WEBSITE_URL;
    const static int SECONDS_FOR_WAITING_ON_RESPONSE = 8;
};

#endif // HTTPREQUESTER_H
