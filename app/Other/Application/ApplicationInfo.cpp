#include "ApplicationInfo.h"

ApplicationInfo::ApplicationInfo()
{
    settings = new QSettings();
    settings->beginGroup("METADATA");
}

ApplicationInfo::~ApplicationInfo()
{
    delete settings;
}

const int ApplicationInfo::versionCode = 3;
const QString ApplicationInfo::versionName = "1.1.0";


int ApplicationInfo::getVersionCode()
{
    return versionCode;
}

QString ApplicationInfo::getVersionName()
{
    return versionName;
}

void ApplicationInfo::initAppliactionPath(QString fullPath)
{

    QStringList splitted = fullPath.split(QDir::separator());
    QString appPath;
    QString appName;

    for(int i = 1; i < splitted.size()-1; i++)
    {
        appPath += QString(QDir::separator()).append(splitted.at(i));
    }
    appName = splitted.at(splitted.size()-1);

    this->applicationPath = appPath;
    this->applicationName = appName;

    if(this->isNotInitializedAppliactionPath())
    {
        settings->setValue("appPath", applicationPath);
    }
    if(this->isNotInitializedAppliactionName())
    {
        settings->setValue("appName", applicationName);
    }
}

bool ApplicationInfo::isNotInitializedAppliactionPath()
{
    return settings->value("appPath").toString().isEmpty();
}

bool ApplicationInfo::isNotInitializedAppliactionName()
{
    return settings->value("appName").toString().isEmpty();
}

QString ApplicationInfo::getApplicationPath()
{
    return settings->value("appPath").toString();
}

QString ApplicationInfo::getApplicationName()
{
    return settings->value("appName").toString();
}
