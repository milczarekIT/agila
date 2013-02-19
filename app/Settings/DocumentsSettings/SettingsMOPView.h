#ifndef SETTINGSMOPVIEW_H
#define SETTINGSMOPVIEW_H

#include <QLabel>
#include <QWidget>
#include <QString>
#include <QSpinBox>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include "Database/Database.h"
#include "Components/Button.h"
#include "Settings/SettingsModel.h"
#include "Document/MethodOfPayment.h"
#include "SettingsMOPController.h"
#include "Settings/SettingsAbstractItemView.h"
class SettingsMOPController;

/**
  @author Janiu
  Klasa widgeta zawierającego elementy ustawień sposobów płatności
  */
class SettingsMOPView  : public SettingsAbstractItemView
{
    Q_OBJECT
  private:
  /**
    Wskaźnik do klasy zawierającej wszystkie kontrolki dla elementów badanego widgeta
  */
    SettingsMOPController *controller;
  /**
     Pola, w których umieszczamy najważniejsze dane o stawce VAT, wykorzystywane do umieszczenia tych danych
     w bazie danych, bądź modyfikacji istniejącch informacji o stawce
  */
    QLineEdit *lineName;
    QSpinBox *spinNumberOfDays;
  /**
    ComboBox który zawiera model odnoszący się do danych o sposobach płatności z bazy danych, w swoim ciele
    wyświetla nazwy tych sposobów
   */
    QComboBox * boxMOPs;
   /**
    Przycisk umożliwiający zapisanie w bazie danych dokonanych zmian
   */
    Button *pushSave;
   /**
    Przycisk umożliwiający edycję wybranego sposobu płatności
   */
    Button *pushEdit;
   /**
    Przycisk umożliwiający dodanie nowego sposobu płatności
   */
    Button *pushNew;
   /**
    Przycisk umożliwiający usunięcie z programu danej jednostki
   */
    Button *pushDelete;

  public:
  /**
    Gettery dla atrybutow/widgetow danej klasy - analogicznie do ich nazwy
   */
    QLineEdit *getLineName();
    QSpinBox *getSpinNumberOfDays();
    QComboBox *getBoxMOPs();
    Button *getPushSave();
    Button *getPushEdit();
    Button *getPushNew();
    Button *getPushDelete();
  /**
    Konstruktor inicjujący wszystkie elementy dla danego widgeta
    @param
    parent - wskaźnik określający rodzica widgeta, wykorzystywany w programie
    controller - wskaźnik do obiektu zawierającego kontrolki dla atrybutów danej klasy
   */
    explicit SettingsMOPView(SettingsMOPController *controller,QWidget *parent = 0);
   /**
    Destruktor dla danej klasy, usuwa smodel
   */
    ~SettingsMOPView();
    void initGraphicElements();
    void setGraphicSettings();
    void setInterfaceController();
};

#endif // SETTINGSMOPVIEW_H
