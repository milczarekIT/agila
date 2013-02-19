#ifndef ARCHIVERSETTINGS_H
#define ARCHIVERSETTINGS_H

#include <QSettings>

/**
  * Ustawienia Archiwizacji
  * @author Bartosz Milczarek
  */
class ArchiverSettings
{
private:
    static const int REMOVE_DEFAULT_DAYS = 90;
    static const int REMIND_DEFAULT_DAYS = 0;

    QSettings settings;
    QString qsettingsGroup;
public:    
    ArchiverSettings();
    ~ArchiverSettings();

    int getRemindDays();
    int getRemoveDays();

    void setRemindDays(int remindDays);
    void setRemoveDays(int removeDays);


};

#endif // ARCHIVERSETTINGS_H
