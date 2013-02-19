#include "NetworkHelper.h"

NetworkHelper::NetworkHelper()
{
}

QString NetworkHelper::macAdress() {

    foreach(QNetworkInterface ni, QNetworkInterface::allInterfaces())
    {
        if(ni.name().startsWith("eth"))
        {
            return ni.hardwareAddress().remove(":");
        }
    }

    // jeśli nie ma karty przewodowej to może być też wlan
    foreach(QNetworkInterface ni, QNetworkInterface::allInterfaces())
    {
        if(ni.name().startsWith("wlan"))
        {
            return ni.hardwareAddress().remove(":");
        }
    }
    return "";
}
