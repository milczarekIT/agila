#ifndef NETWORKHELPER_H
#define NETWORKHELPER_H

#include <QNetworkInterface>

class NetworkHelper
{
public:
    NetworkHelper();

    static QString macAdress();
};

#endif // NETWORKHELPER_H
