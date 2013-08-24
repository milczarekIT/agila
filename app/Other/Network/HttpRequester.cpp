#include "HttpRequester.h"

HttpRequester::HttpRequester()
{

}

HttpRequester::~HttpRequester() {}

const QString HttpRequester::WEBSITE_URL = "http://agila.bluebraces.com";

QString HttpRequester::sendAgilaServiceRequest(QString serviceName, QStringList args) {      // throws NoHttpResponseException

    QString serviceUrl = WEBSITE_URL + "/service/" + serviceName;
    foreach(QString arg, args) {
        serviceUrl.append("/" + arg);
    }

    networkManager = new QNetworkAccessManager(this);
    reply = networkManager->get(QNetworkRequest(QUrl(serviceUrl)));

    loop = new QEventLoop();
    QObject::connect(reply, SIGNAL(readyRead()), loop, SLOT(quit()));

    QTimer *idleTimer = new QTimer(this);
    connect(idleTimer,SIGNAL(timeout()),loop,SLOT(quit()));
    idleTimer->setInterval(SECONDS_FOR_WAITING_ON_RESPONSE * 1000);

    idleTimer->start();
    loop->exec();

    QString response = reply->readAll();

    networkManager->deleteLater();
    reply->deleteLater();

    if(response.isEmpty())
        throw new NoHttpResponseException("HttpRequester::sendRequest()");

    return response;
}

QFile *HttpRequester::downloadFile(QString fileUrl) {

    networkManager = new QNetworkAccessManager(this);
    reply = networkManager->get(QNetworkRequest(QUrl(fileUrl)));

    loop = new QEventLoop();
    QObject::connect(reply, SIGNAL(readyRead()), loop, SLOT(quit()));

    QTimer *idleTimer = new QTimer(this);
    connect(idleTimer,SIGNAL(timeout()),loop,SLOT(quit()));
    idleTimer->setInterval(SECONDS_FOR_WAITING_ON_RESPONSE * 1000);
    idleTimer->start();


    loop->exec();

    QString fileName = QFileInfo(fileUrl).fileName();
    QFile *file = new QFile(fileName);
    file->open(QIODevice::WriteOnly);
    file->write(reply->readAll());
    file->close();

    networkManager->deleteLater();
    reply->deleteLater();

    return file;
}




