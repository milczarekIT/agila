#include "ArchiverSettings.h"

ArchiverSettings::ArchiverSettings()
{
    qsettingsGroup = "Backup";
}

ArchiverSettings::~ArchiverSettings()
{
}

int ArchiverSettings::getRemindDays()
{
    settings.beginGroup(qsettingsGroup);
    int remindDays = settings.value("remindDays", REMIND_DEFAULT_DAYS).toInt();
    settings.endGroup();

    return remindDays;
}

int ArchiverSettings::getRemoveDays()
{
    settings.beginGroup(qsettingsGroup);
    int removeDays = settings.value("removeDays", REMOVE_DEFAULT_DAYS).toInt();
    settings.endGroup();

    return removeDays;
}

void ArchiverSettings::setRemindDays(int remindDays)
{
    settings.beginGroup(qsettingsGroup);
    settings.setValue("remindDays", remindDays);
    settings.endGroup();
}

void ArchiverSettings::setRemoveDays(int removeDays)
{
    settings.beginGroup(qsettingsGroup);
    settings.setValue("removeDays", removeDays);
    settings.endGroup();
}


