#ifndef ARCHIVERAUTOREMOVER_H
#define ARCHIVERAUTOREMOVER_H

#include <QFileInfoList>
#include "Components/FileInfo.h"
#include "Tools/Archiver/ArchiverService.h"
#include "Tools/Archiver/ArchiverSettings.h"

/**
  * Klasa odpowiedziala za automatyczne kasowanie starych kopii zapasowaych przy starcie programu
  * @author Bartosz Milczarek
  */
class ArchiverAutoRemover
{
private:
    ArchiverService *service;
    ArchiverSettings *settings;

    QFileInfoList archiveFileinfoList;
    QDate removeDate;
    int removeDays;

    bool isRemovingOn();
    void removeOldBackups();
    QDate getRemoveDate();
    bool isFileToRemove(QDate backupFileDate);

public:
    ArchiverAutoRemover();
    ~ArchiverAutoRemover();

    /**
      * Metoda sprawdzająca czy użytkownik chce kasować stare kopie zapasowe,
      * jeśli tak to usuwa je zgodnie z ustawieniami o przchowywaniu kopii zapasowych
      */
    void checkAndRemoveOldBackups();
};

#endif // ARCHIVERAUTOREMOVER_H
