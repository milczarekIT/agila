#ifndef SETTINGSABSTRACTITEMVIEW_H
#define SETTINGSABSTRACTITEMVIEW_H

#include <QScrollArea>
#include <QGridLayout>
#include "Components/MessageBox.h"

class SettingsAbstractItemView : public QWidget
{
    Q_OBJECT
private:
    /**
     Metoda ustawiająca widgety okna w odpowiednich miejscach layoutu
    */
    virtual void initGraphicElements() = 0;
    /**
     Metoda ingerująca w ustawienia layoutu oraz stan i wygląd widgetów
    */
    virtual void setGraphicSettings() = 0;
    /**
     Metoda nadająca kontrolę odpowiednim widgetom w module
    */
    virtual void setInterfaceController() = 0;

protected:
    /**
      MessageBox ktory wyswietla uzytkownikowi informacje badz zapytanie o dokonanie operacji
    */
    MessageBox *messageBox;
    QGridLayout *mainLayout;

public:
    explicit SettingsAbstractItemView(QWidget *parent = 0);
    MessageBox *getMessageBox();

signals:
    void changesWereMade();

public slots:
    void emitChangesWereMade();

};

#endif // SETTINGSABSTRACTITEMVIEW_H
