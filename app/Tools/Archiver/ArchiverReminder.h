#ifndef ARCHIVERREMINDER_H
#define ARCHIVERREMINDER_H

#include <QDateTime>
#include "Components/MessageBox.h"
#include "Components/FileInfo.h"
#include "Tools/Archiver/ArchiverSettings.h"
#include "Tools/Archiver/ArchiverService.h"

/**
  * Klasa odpowiedzialna za przypomnienia o archwizacji przy końcu aplikacji
  * @author Bartosz Milczarek
  */
class ArchiverReminder
{
private:
    ArchiverService *service;
    ArchiverSettings *settings;

    int remindDays;
    QFileInfoList archiveFileInfoList;
    QDateTime lastBackupDateTime;

    bool isRemindingOn();
    void remindIfNeeded();

    bool isBackupCreatedEalier();
    bool isExpiredAvailableBackupTime();

    QDateTime getLastBackupDateTime();
    QDate getLastAllowedBackupDate();
    int getDaysSinceLastBackup();

    QFileInfo getLastBackupFileInfo();
    void sortArchiveFileInfoListByCreatedDate();

    void showStandardRemind();
    void showFirstRemind();

public:
    ArchiverReminder();
    ~ArchiverReminder();

    /**
      * Sprawdza preferencje użytkowika i przypomina o archiwizacji jeśli istnieje taka potzreba
      */
    void checkPreferencesAndRemind();
};

#endif // ARCHIVERREMINDER_H
