#ifndef UPDATEINFO_H
#define UPDATEINFO_H

#include <QString>

class UpdateInfo
{
    int newVersionCode;
    QString newVersionName;
    QString downloadLink;
public:
    UpdateInfo();

    void setNewVersionCode(int newVersionCode);
    void setNewVersionName(QString newVersionName);
    void setDownloadLink(QString downloadLink);

    int getNewVersionCode();
    QString getNewVersionName();
    QString getDownloadLink();

};

#endif // UPDATEINFO_H
