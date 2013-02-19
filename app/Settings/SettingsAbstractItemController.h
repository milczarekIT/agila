#ifndef SETTINGSABSTRACTITEMCONTROLLER_H
#define SETTINGSABSTRACTITEMCONTROLLER_H

#include <QObject>

class SettingsAbstractItemController : public QObject
{
    Q_OBJECT

public:
    explicit SettingsAbstractItemController(QObject *parent = 0);
    //virtual void setModel() = 0;

    static const int IDLE = 0;
    static const int EDIT = 1;
    static const int ADD = 2;

    int getButtonStatus();
    void setButtonStatus(int buttonStatus);

protected:
    /**
      Liczba całkowita określająca czy ustawienia są w stanie edycji, dodawania nowej stawki czy przeglądania
      tabeli
     */
    int buttonStatus;


};

#endif // SETTINGSABSTRACTITEMCONTROLLER_H
