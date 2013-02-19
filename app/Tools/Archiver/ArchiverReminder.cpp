#include "ArchiverReminder.h"

ArchiverReminder::ArchiverReminder()
{
    service = new ArchiverService();
    settings = new ArchiverSettings();

    remindDays = settings->getRemindDays();
    archiveFileInfoList = service->getArchiveFileInfoList();
    lastBackupDateTime = this->getLastBackupDateTime();
}

ArchiverReminder::~ArchiverReminder()
{
    delete service;
    delete settings;
}

void ArchiverReminder::checkPreferencesAndRemind()
{
    if(isRemindingOn())
        remindIfNeeded();
}

bool ArchiverReminder::isRemindingOn() {
    return remindDays > 0;
}

void ArchiverReminder::remindIfNeeded()
{
    if(isBackupCreatedEalier())
    {
        if(isExpiredAvailableBackupTime())
            showStandardRemind();
    }
    else
        showFirstRemind();
}

bool ArchiverReminder::isBackupCreatedEalier() {

    if(archiveFileInfoList.size() == 0)
        return false;
    else
        return true;
}

bool ArchiverReminder::isExpiredAvailableBackupTime()
{
    return getLastBackupDateTime().date() <= getLastAllowedBackupDate();
}

QDateTime ArchiverReminder::getLastBackupDateTime()
{
    QFileInfo lastBackupFileInfo = getLastBackupFileInfo();

    return FileInfo::lowerDate(lastBackupFileInfo);
}

QDate ArchiverReminder::getLastAllowedBackupDate()
{
    return QDate::currentDate().addDays(- remindDays);
}

QFileInfo ArchiverReminder::getLastBackupFileInfo() {
    sortArchiveFileInfoListByCreatedDate();

    if(archiveFileInfoList.size() > 0)
            return archiveFileInfoList[0];
        else
            return QFileInfo();
}

void ArchiverReminder::sortArchiveFileInfoListByCreatedDate() {
    QFileInfo temp;
    for (int i = 0; i < archiveFileInfoList.size(); i++)
    {
        for (int j=0; j < archiveFileInfoList.size()-1; j++)
        {
            QDateTime dateTime = FileInfo::lowerDate(archiveFileInfoList.at(j));
            QDateTime nextDateTime = FileInfo::lowerDate(archiveFileInfoList.at(j+1));
            if (dateTime < nextDateTime)
            {
                temp = archiveFileInfoList[j+1];
                archiveFileInfoList[j+1] = archiveFileInfoList[j];
                archiveFileInfoList[j] = temp;
            }
        }
    }
}

void ArchiverReminder::showStandardRemind()
{
    QString text = "Czy chcesz utworzyć kopię bezpieczenstwa?";
    QString informativeText = "Ostatnia wykonano kopię zapasową " +QString::number(getDaysSinceLastBackup()) + " dni temu ("
                              + lastBackupDateTime.toString("yyyy-MM-dd hh:mm") + ")"
                               "\n\nMożesz wyłączyć przypomnienia w \nInne > Archiwizacja";
    MessageBox *messageBox = new MessageBox();
    if (messageBox->createQuestionBox(text, informativeText) == MessageBox::YES)
    {
        service->createBackup();
    }
}

void ArchiverReminder::showFirstRemind()
{
    QString informativeText = "Nie utworzyłeś jeszcze kopii bezpieczeństwa. Zaleca się regularnie tworzenie takich kopii, "
                              "w celu zapobiegnięcia utraty danych. Czy chcesz utworzyć teraz kopię bezpieczeństwa?"
                              "\n\nMożesz wyłączyć przypomnienia w: \nInne > Archiwizacja";
    MessageBox *messageBox = new MessageBox();
    if (messageBox->createQuestionBox("Czy chcesz utworzyć kopię bezpieczenstwa?", informativeText) == MessageBox::YES)
    {
       service->createBackup();
    }
}


int ArchiverReminder::getDaysSinceLastBackup() {
    return lastBackupDateTime.date().daysTo(QDate::currentDate());
}
