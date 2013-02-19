#include "ArchiverService.h"

ArchiverService::ArchiverService()
{
}

QString ArchiverService::ARCHIVE_DIR = ApplicationManager::DIR_HOME_AGILA + QDir::separator() + "archives";

QFileInfoList ArchiverService::getArchiveFileInfoList()
{
    QDir dir(ArchiverService::ARCHIVE_DIR);
    return dir.entryInfoList(QStringList("*.dump"));
}

void ArchiverService::createBackup()
{
    prepareArchiveDir();
    QString filePrefix = QCoreApplication::applicationName().toLower().trimmed().replace(" ", "_");
    prepareFileName(filePrefix, "dump");
    archivePath = ArchiverService::ARCHIVE_DIR + QDir::separator() + this->fileName;

    this->callDumpingProcess();
}

void ArchiverService::restoreBackup(QString sqlFileName)
{
    this->callRestoringProcess(sqlFileName);
}

void ArchiverService::removeBackup(QString sqlFileName)
{
    QFile(ArchiverService::ARCHIVE_DIR + QDir::separator() + sqlFileName).remove();
}

void ArchiverService::prepareFileName(QString filePrefix, QString extension)
{
    QDateTime now = QDateTime::currentDateTime();
    fileName = filePrefix + "_" + now.toString("yyMMdd") + "_" + now.toString("hhmm") + "." + extension;
}

void ArchiverService::prepareArchiveDir()
{
    QString archivePath = ArchiverService::ARCHIVE_DIR;
    QDir archiveDir(archivePath);

    if(!archiveDir.exists(archivePath))
        archiveDir.mkdir(archivePath);
}

void ArchiverService::callDumpingProcess()
{
    pgdumpProc = new QProcess();
    connect(pgdumpProc, SIGNAL(readyReadStandardError()), this, SLOT(readyReadStandardErrorSlot()));
    connect(pgdumpProc, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(finishedArchiveSlot(int)));

    arguments << "-h";
    arguments << "localhost";
    arguments << "-U";
    arguments << Database::getInstance().db.userName();
    arguments << "--clean";
    arguments << "--no-privileges";
    arguments << "--no-owner";
    arguments << Database::getInstance().db.databaseName();

    pgdumpProc->setStandardOutputFile(this->archivePath);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    pgdumpProc->start("pg_dump", arguments);
    pgdumpProc->waitForFinished();
    QApplication::restoreOverrideCursor();

    delete pgdumpProc;
}

void ArchiverService::callRestoringProcess(QString sqlFileName)
{
    pgdumpProc = new QProcess();
    connect(pgdumpProc, SIGNAL(readyReadStandardError()), this, SLOT(readyReadStandardErrorSlot()));
    connect(pgdumpProc, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(finishedRestoreSlot(int)));

    arguments << "-U";
    arguments << Database::getInstance().db.userName();
    arguments << Database::getInstance().db.databaseName();
    // psql: FATAL:  Peer authentication failed for user "bbraces"

    pgdumpProc->setStandardInputFile(sqlFileName);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    pgdumpProc->start("psql", arguments);
    pgdumpProc->waitForFinished();
    QApplication::restoreOverrideCursor();

    delete pgdumpProc;
}



void ArchiverService::finishedArchiveSlot(int exitCode)
{
  if (exitCode == QProcess::NormalExit)
    QMessageBox::information(0, "Wykonano", tr("Zarchiwizowano pomyślnie"));
}

void ArchiverService::finishedRestoreSlot(int exitCode)
{
  if (exitCode == QProcess::NormalExit)
    QMessageBox::information(0, "Wykonano", tr("Przywrócono bazę pomyślnie"));
}

void ArchiverService::readyReadStandardErrorSlot()
{
  QApplication::restoreOverrideCursor();
  QString errors = QString(pgdumpProc->readAllStandardError());
  errors = errors.remove("ERROR:  must be owner of schema public");
  errors = errors.remove("ERROR:  schema \"public\" already exists");
  errors = errors.remove("ERROR:  must be owner of schema public");
  errors = errors.remove("ERROR:  must be owner of extension plpgsql");
  errors.remove("\n");

  if(errors.length() > 0) {
    QMessageBox::warning(0, "Błędy", errors);
    pgdumpProc->close();
  }
}

ArchiverService::~ArchiverService()
{

}
