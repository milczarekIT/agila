#ifndef SETTINGSUNITSVIEW_H
#define SETTINGSUNITSVIEW_H

#include <QLabel>
#include <QWidget>
#include <QString>
#include <QSpinBox>
#include <QLineEdit>
#include <QGridLayout>
#include <QComboBox>
#include "Goods/Unit.h"
#include "Components/Button.h"
#include "Database/Database.h"
#include "Settings/SettingsModel.h"
#include "SettingsUnitsController.h"
#include "Settings/SettingsAbstractItemView.h"
class SettingsUnitsController;

/**
  @author Janiu
  Klasa widgeta zawierającego elementy ustawień jednostek miary
  */

class SettingsUnitsView : public SettingsAbstractItemView
{
    Q_OBJECT
private:
  /**
    Wskaźnik do klasy zawierającej wszystkie kontrolki dla elementów badanego widgeta
  */
    SettingsUnitsController *controller;
  /**
     Pola, w których umieszczamy najważniejsze dane o stawce VAT, wykorzystywane do umieszczenia tych danych
     w bazie danych, bądź modyfikacji istniejącch informacji o stawce
  */
    QLineEdit *lineName;
    QSpinBox *spinZeroPlaces;
  /**
    ComboBox który zawiera model odnoszący się do danych o jednostkach z bazy danych, w swoim ciele
    wyświetla nazwy tych jednostek
  */
    QComboBox *boxUnits;
  /**
    Przycisk umożliwiający zapisanie w bazie danych dokonanych zmian
   */
    Button *pushSave;
  /**
    Przycisk umożliwiający edycję wybranej jednostki
   */
    Button *pushEdit;
  /**
    Przycisk umożliwiający dodanie nowej jednostki
   */
    Button *pushNew;
  /**
    Przycisk umożliwiający usunięcie z programu danej jednostki
   */
    Button *pushDelete;

    void initGraphicElements();
    void setGraphicSettings();
    void setInterfaceController();

public:
  /**
    Gettery dla atrybutow/widgetow danej klasy - analogicznie do ich nazwy
   */
    QLineEdit *getLineName();
    QSpinBox *getSpinZeroPlaces();
    QComboBox *getBoxUnits();
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
    explicit SettingsUnitsView(SettingsUnitsController *controller,QWidget *parent = 0);
  /**
    Destruktor dla danej klasy, usuwa smodel
   */
    ~SettingsUnitsView();
};

#endif // SETTINGSUNITSVIEW_H
