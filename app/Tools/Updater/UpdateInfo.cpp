#include "UpdateInfo.h"

UpdateInfo::UpdateInfo()
{
}


void UpdateInfo::setNewVersionCode(int newVersionCode) {
    this->newVersionCode = newVersionCode;
}

void UpdateInfo::setNewVersionName(QString newVersionName) {
    this->newVersionName = newVersionName;
}

void UpdateInfo::setDownloadLink(QString downloadLink) {
    this->downloadLink = downloadLink;
}

int UpdateInfo::getNewVersionCode() {
    return this->newVersionCode;
}

QString UpdateInfo::getNewVersionName() {
    return this->newVersionName;
}

QString UpdateInfo::getDownloadLink() {
    return this->downloadLink;
}
