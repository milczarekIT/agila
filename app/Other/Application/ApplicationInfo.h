#ifndef APPLICATIONINFO_H
#define APPLICATIONINFO_H

#include <QString>
#include <QSettings>
#include <QDir>
#include <QDebug>

class ApplicationInfo
{
private:
    /**
      * Wersja kodu
      */
    static const int versionCode;

    /**
      * Nazwa wersji
      */
    static const QString versionName;


    QSettings *settings;
    QString applicationPath;
    QString applicationName;

    bool isNotInitializedAppliactionPath();
    bool isNotInitializedAppliactionName();
public:
    ApplicationInfo();
    ~ApplicationInfo();

    static int getVersionCode();
    static QString getVersionName();

    /**
      * Zwraca nazwę pliku zainstalowanej aplikacji np. Agila, Agila.exe
      */
    QString getApplicationName();

    /**
      * Zwraca pełną ścieżkę do zainstalowanej aplikacji
      */
    QString getApplicationPath();

    /**
      * Inicjalizuje w QSettings ścięzkę do aplikacji
      * @param
      */
    void initAppliactionPath(QString fullPath);
};

#endif // APPLICATIONINFO_H
