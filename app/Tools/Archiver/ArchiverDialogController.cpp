#include "ArchiverDialogController.h"

ArchiverDialogController::ArchiverDialogController(QWidget *parent)
{
    this->view = new ArchiverDialogView(parent, this);
    this->settings = new ArchiverSettings();
    messageBox = new MessageBox();

    restoreTableState();
}

ArchiverDialogController::~ArchiverDialogController()
{
    saveTableState();
    delete view;
    delete settings;
    delete messageBox;
}

bool ArchiverDialogController::exec()
{
    readSettings();
    initSpinBoxesData();
    getFileList();

    int signal = view->exec();

    if(signal == QDialog::Accepted)
    {
        saveSettings();
        return true;
    }
    else
        return false;
}

void ArchiverDialogController::getFileList()
{
    QFileInfoList fileInfoList = service->getArchiveFileInfoList();
    QString size;
    for(int i = 0; i < view->getTableModel()->rowCount(); i++)
    {
        view->getTableModel()->removeRow(i);
    }
    for(int i = 0; i < fileInfoList.size(); i++)
    {        
        size = FileInfo::sizeToStringWithUnit(fileInfoList.at(i));
        view->getTableModel()->setItem(i, 0, new QStandardItem(fileInfoList.at(i).fileName()));
        view->getTableModel()->setItem(i, 1, new QStandardItem(size));
        view->getTableModel()->setItem(i, 2, new QStandardItem(FileInfo::lowerDate(fileInfoList.at(i)).toString("yyyy-MM-dd hh:mm")));
    }
    view->getTable()->sortByColumn(2, Qt::DescendingOrder);
}

void ArchiverDialogController::readSettings()
{
    remindDays = oldRemindDays = settings->getRemindDays();
    removeDays = oldRemoveDays = settings->getRemoveDays();
}

void ArchiverDialogController::saveSettings()
{
    if(view->getRadioRemind()->isChecked())
        remindDays = view->getSpinRemind()->value();
    else
        remindDays = 0;

    if(view->getRadioRemove()->isChecked())
        removeDays = view->getSpinRemove()->value();
    else
        removeDays = 0;

    if((removeDays != oldRemoveDays) || (remindDays != oldRemindDays))
    {
        settings->setRemindDays(remindDays);
        settings->setRemoveDays(removeDays);
    }
}

void ArchiverDialogController::initSpinBoxesData()
{
    if(remindDays == 0) // nie przypominaj
    {
        view->getSpinRemind()->setValue(15); // wartośtość domyślna
        view->getRadioDontRemind()->setChecked(true);
        view->getRadioRemind()->setChecked(false);
    }
    else
    {
        view->getSpinRemind()->setValue(remindDays);
        view->getRadioDontRemind()->setChecked(false);
        view->getRadioRemind()->setChecked(true);
    }
    if(removeDays == 0) // nie usuwaj
    {
        view->getSpinRemove()->setValue(90);
        view->getRadioDontRemove()->setChecked(true);
        view->getRadioRemove()->setChecked(false);
    }
    else
    {
        view->getSpinRemove()->setValue(removeDays);
        view->getRadioDontRemove()->setChecked(false);
        view->getRadioRemove()->setChecked(true);
    }
}

void ArchiverDialogController::changesAtSpinRemind(int value)
{
    if(value == 0)
        view->getRadioDontRemind()->setChecked(true);
    else
        view->getRadioRemind()->setChecked(true);
}

void ArchiverDialogController::changesAtSpinRemove(int value)
{
    if(value == 0)
        view->getRadioDontRemove()->setChecked(true);
    else
        view->getRadioRemove()->setChecked(true);
}

void ArchiverDialogController::createBackup()
{
    this->service = new ArchiverService();
    service->createBackup();
    delete service;
    getFileList();
}

void ArchiverDialogController::restoreBackup()
{
    fileName = view->getSelectedFileName();
    if(isFileSelected())
    {
        QString path = ArchiverService::ARCHIVE_DIR + QDir::separator() + fileName;
        QString text = "Przywracanie kopi bezpieczeństwa z dn. " + QFileInfo(path).created().toString("yyyy-MM-dd hh:mm");
        QString informativeText = "Przywrócenie kopi bezpieczeństwa oznacza skasowanie wszystkich danych i załadowanie danych z kopii bezpieczeństwa utworzonej wcześniej. Czy napewno przywrócić dane?";
        if (messageBox->createQuestionBox(text, informativeText) == MessageBox::YES)
        {
            this->service = new ArchiverService();
            service->restoreBackup(path);
            delete service;
        }
    }
    else
        showMessageFileNotSelected();

}

void ArchiverDialogController::removeBackup()
{
    fileName = view->getSelectedFileName();
    if(isFileSelected())
    {
        if (messageBox->createQuestionBox("Czy napewno usunąć kopię bezpieczeństwa?", "") == MessageBox::YES)
        {
            this->service = new ArchiverService();
            service->removeBackup(fileName);
            delete service;
            this->getFileList();
        }
    }
    else       
        showMessageFileNotSelected();

}

bool ArchiverDialogController::isFileSelected() {
    return !fileName.isEmpty();
}

void ArchiverDialogController::showMessageFileNotSelected()
{
    messageBox->createInfoBox("Zaznacz plik");
}

void ArchiverDialogController::restoreTableState() {
    tableStateManager = new TableStateManager();
    QByteArray state = tableStateManager->getState("ARCHIVER_DIALOG");
    view->getTable()->horizontalHeader()->restoreState(state);

    delete tableStateManager;
}

void ArchiverDialogController::saveTableState() {
    tableStateManager = new TableStateManager();
    QByteArray state = view->getTable()->horizontalHeader()->saveState();
    QByteArray oldState = tableStateManager->getState("ARCHIVER_DIALOG");
    if(state != oldState)
        tableStateManager->saveState("ARCHIVER_DIALOG", state);

    delete tableStateManager;
}


