#ifndef SETTINGSOWNERVIEW_H
#define SETTINGSOWNERVIEW_H

#include <QLabel>
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include "Components/Button.h"
#include "SettingsOwnerController.h"
#include "Settings/SettingsAbstractItemView.h"
class SettingsOwnerController;

/**
  @author Janiu
  Klasa widgeta zawierającego elementy ustawień podmiotu
  */
class SettingsOwnerView : public SettingsAbstractItemView
{
    Q_OBJECT
private:
  /**
    Wskaźnik do klasy zawierającej wszystkie kontrolki dla elementów badanego widgeta
  */
    SettingsOwnerController *controller;
  /**
    Pola, w których umieszczamy najważniejsze dane o podmiocie, wykorzystywane do umieszczenia tych danych
    w pliku xml, bądź modyfikacji istniejącch informacji o podmiocie
  */
    QLineEdit *lineName;
    QLineEdit *lineAdress;
    QLineEdit *linePostCode;
    QLineEdit *lineCity;
    QLineEdit *lineNIP;
    QLineEdit *lineBankName;
    QLineEdit *lineBankAccount;
    QLineEdit *lineEMail;
    QLineEdit *lineWebsite;
    QLineEdit *linePhone1;
    QLineEdit *linePhone2;
    QLineEdit *linePhone3;
    QTextEdit *textAdditional;
  /**
    Pole zawierające logo podmiotu
   */
    QLabel *logo;
  /**
    Przycisk umożliwiający zapisanie w pliku xml dokonanych zmian
   */
    Button *pushSave;
  /**
    Przycisk zmiany/dodawania logo podmiotu
    */
    Button *pushSetLogo;
  /**
    Przycisk usunięcia logo podmiotu
    */
    Button *pushRemoveLogo;

public:
  /**
    Konstruktor inicjujący wszystkie elementy dla danego widgeta
    @param
    parent - wskaźnik określający rodzica widgeta, wykorzystywany w programie
    controller - wskaźnik do obiektu zawierającego kontrolki dla atrybutów danej klasy
  */
    explicit SettingsOwnerView(SettingsOwnerController *controller,QWidget *parent = 0);
  /**
    Gettery dla atrybutow/widgetow danej klasy - analogicznie do ich nazwy
   */
    QLineEdit *getLineName();
    QLineEdit *getLineAdress();
    QLineEdit *getLinePostCode();
    QLineEdit *getLineCity();
    QLineEdit *getLineNIP();
    QLineEdit *getLineBankName();
    QLineEdit *getLineBankAccount();
    QLineEdit *getLineEMail();
    QLineEdit *getLineWebsite();
    QLineEdit *getLinePhone1();
    QLineEdit *getLinePhone2();
    QLineEdit *getLinePhone3();
    QTextEdit *getTextAdditional();
    Button *getPushSave();
    Button *getPushRemoveLogo();
    Button *getPushSetLogo();
    QLabel *getLogo();
    void initGraphicElements();
    void setGraphicSettings();
    void setInterfaceController();
};

#endif // SETTINGSOWNERVIEW_H
