#ifndef ARCHIVERDIALOGCONTROLLER_H
#define ARCHIVERDIALOGCONTROLLER_H

#include <QDebug>
#include <QWidget>
#include <QDateTime>
#include <QProcess>
#include <QMessageBox>
#include <QObject>
#include "Database/Database.h"
#include "Components/MessageBox.h"
#include "Components/FileInfo.h"
#include "Tools/Archiver/ArchiverDialogView.h"
#include "Tools/Archiver/ArchiverService.h"
#include "Tools/Archiver/ArchiverSettings.h"
#include "Other/ITableStateManager.h"
class ArchiverDialogView;

/**
  * Kontroler okna Archiwizacji
  * @author Bartosz Milczarek
  */
class ArchiverDialogController : public QObject, public ITableStateManager
{
    Q_OBJECT
private:

    ArchiverDialogView *view;
    ArchiverService *service;
    ArchiverSettings *settings;

    MessageBox *messageBox;

    int remindDays, removeDays, oldRemindDays, oldRemoveDays;
    QString fileName;

    /** pobiera listę plików */
    void getFileList();

    /** Wczytuje i zapisuj ustawienia dot. archiwizacji (przypomnienia o archiwizacji, usuwanie starych wersji */
    void readSettings();
    void saveSettings();
    void initSpinBoxesData();

    bool isFileSelected();

    void showMessageFileNotSelected();

    void restoreTableState();
    void saveTableState();
public:
    ArchiverDialogController(QWidget *parent);
    ~ArchiverDialogController();

    bool exec();

public slots:
    void changesAtSpinRemind(int value);
    void changesAtSpinRemove(int value);

    void createBackup();
    void restoreBackup();
    void removeBackup();
};

#endif // ARCHIVERDIALOGCONTROLLER_H
