#ifndef SETTINGSPREFERENCE_H
#define SETTINGSPREFERENCE_H

#include <QString>

class SettingsPreference
{
public:
    SettingsPreference();

    static const QString PRINT_ACTION_PRINT_AND_PDF;
    static const QString PRINT_ACTION_PRINT_ONLY;
    static const QString PRINT_ACTION_PDF_ONLY;
};

#endif // SETTINGSPREFERENCE_H
