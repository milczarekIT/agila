#ifndef ARCHIVERSERVICE_H
#define ARCHIVERSERVICE_H

#include <QMessageBox>
#include <QApplication>
#include "Database/Database.h"
#include "Components/MessageBox.h"
#include "Other/Application/ApplicationManager.h"

class ArchiverService : public QObject
{
    Q_OBJECT

    QString archivePath;
    QString fileName;
    QProcess *pgdumpProc;

    /** argumenty dla mysqldump dla QProcess proc */
    QStringList arguments;

    /**
      * Przygotowanie nazwy pliku (this->fileName)
      * Nazwa tworzona jest wg szablonu: nazwabazy_data_czas.extension
      * @param filePrefix - początek nazwy pliku np. nazwa bazy danych
      * @param extension - rozszerzenie pliku: exenstion = "sql" || extension = "xml"
      * @see archiveSql();
      */
    void prepareFileName(QString filePrefix, QString extension);
    void prepareArchiveDir();

    void callDumpingProcess();
    void callRestoringProcess(QString sqlFileName);

public:
    ArchiverService();
    ~ArchiverService();

    static QString ARCHIVE_DIR;

    QFileInfoList getArchiveFileInfoList();

    void createBackup();
    void restoreBackup(QString sqlFileName);
    void removeBackup(QString sqlFileName);

private slots:
    /**
      * Sloty wywoływane po zakończonym procesie archiwizacji/przywracania
      */
    void finishedArchiveSlot(int exitCode);
    void finishedRestoreSlot(int exitCode);

    /**
      * Slot wyświetlający w oknie ostrzegającym informacje o powstałych błędach
      */
    void readyReadStandardErrorSlot();
};

#endif // ARCHIVERSERVICE_H
