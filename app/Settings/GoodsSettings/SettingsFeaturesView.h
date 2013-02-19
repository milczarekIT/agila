#ifndef SETTINGSFEATURESVIEW_H
#define SETTINGSFEATURESVIEW_H

#include <QLabel>
#include <QWidget>
#include <QString>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include "Components/Button.h"
#include "Database/Database.h"
#include "Settings/SettingsAbstractItemView.h"
#include "SettingsFeaturesController.h"
class SettingsFeaturesController;

/**
  @author Janiu
  Klasa widgeta zawierającego elementy ustawień cech towarowych
  */
class SettingsFeaturesView : public SettingsAbstractItemView
{
    Q_OBJECT
private:
  /**
    Wskaźnik do klasy zawierającej wszystkie kontrolki dla elementów badanego widgeta
  */
    SettingsFeaturesController *controller;
  /**
     Pola, w których umieszczamy najważniejsze dane o  cechach towarowych, wykorzystywane do umieszczenia tych danych
     w bazie danych, bądź modyfikacji istniejącch informacji o  cechach
  */
    QLineEdit *lineName;
  /**
    ComboBox który zawiera model odnoszący się do danych o  cechach towarowych z bazy danych, w swoim ciele
    wyświetla nazwy tych  cech
  */
    QComboBox * boxFeatures;
  /**
    Przycisk umożliwiający zapisanie w bazie danych dokonanych zmian
  */
    Button *pushSave;
  /**
    Przycisk umożliwiający edycję wybranej  cechy towarowej
   */
    Button *pushEdit;
  /**
    Przycisk umożliwiający dodanie nowej  cechy towarowej
   */
    Button *pushNew;
  /**
    Przycisk umożliwiający usunięcie z programu danej  cechy towarowej
   */
    Button *pushDelete;

public:
  /**
    Gettery dla atrybutow/widgetow danej klasy - analogicznie do ich nazwy
   */
    QLineEdit *getLineName();
    QComboBox *getBoxFeatures();
    Button *getPushSave();
    Button *getPushEdit();
    Button *getPushNew();
    Button *getPushDelete();
    int getButtonStatus();
    void setButtonStatus(int statusButton);
  /**
    Konstruktor inicjujący wszystkie elementy dla danego widgeta
    @param
    parent - wskaźnik określający rodzica widgeta, wykorzystywany w programie
    controller - wskaźnik do obiektu zawierającego kontrolki dla atrybutów danej klasy
  */
    explicit SettingsFeaturesView(SettingsFeaturesController *controller,QWidget *parent = 0);
  /**
    Destruktor dla danej klasy, usuwa smodel
   */
    ~SettingsFeaturesView();
    void initGraphicElements();
    void setGraphicSettings();
    void setInterfaceController();
};

#endif // SETTINGSFEATURESVIEW_H
