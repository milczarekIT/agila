#include "ArchiverAutoRemover.h"

ArchiverAutoRemover::ArchiverAutoRemover()
{
    service = new ArchiverService();
    settings = new ArchiverSettings();

    removeDays = settings->getRemoveDays();
    archiveFileinfoList = service->getArchiveFileInfoList();
}

ArchiverAutoRemover::~ArchiverAutoRemover()
{
    delete service;
    delete settings;
}

void ArchiverAutoRemover::checkAndRemoveOldBackups()
{
    if(isRemovingOn())
        removeOldBackups();
}

bool ArchiverAutoRemover::isRemovingOn() {
    return removeDays > 0;
}

void ArchiverAutoRemover::removeOldBackups() {

    removeDate =  getRemoveDate();

    QDate backupFileDate;
    for(int i = 0; i < archiveFileinfoList.size(); i++)
    {
        backupFileDate = FileInfo::lowerDate(archiveFileinfoList.at(i)).date();

        if(isFileToRemove(backupFileDate))
            service->removeBackup(archiveFileinfoList.at(i).fileName());
    }
}

QDate ArchiverAutoRemover::getRemoveDate() {
    return QDate::currentDate().addDays(- removeDays);
}

bool ArchiverAutoRemover::isFileToRemove(QDate backupFileDate) {
    return backupFileDate < removeDate;
}
