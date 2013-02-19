#include "Service.h"

Service::Service()
{
}

void Service::showErrorInfo(Exception *e)
{
    qDebug() << "Błąd zapsiu w metodzie: "  << e->getSourceMethod();
    qDebug() << "Message: " << e->getMessage();
}
