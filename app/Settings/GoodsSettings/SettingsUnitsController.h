#ifndef SETTINGSUNITSCONTROLLER_H
#define SETTINGSUNITSCONTROLLER_H

#include <QWidget>
#include "Database/Database.h"
#include "Components/MessageBox.h"
#include "SettingsUnitsView.h"
#include "Settings/SettingsAbstractItemController.h"

class SettingsUnitsView;
/**
  @author Janiu
  Klasa odpowiedzialna za nadanie kontrolek zakładce ustawień jednostek miary dla tabWidgetSettings.
  */
class SettingsUnitsController : public SettingsAbstractItemController
{
    Q_OBJECT
private:
 /**
   QWidget z gama elementów służącą do ustawień jednostek miary, wykorzystywany do nadania mu odpowiedniej funkcjonalności
  */
   SettingsUnitsView *view;
   UnitModel *unitModel;
   void fillBox(QComboBox *box,QVector<Unit> values);
   bool checkFillInTheFields();

public:
  /**
     Konstruktor inicjujący wskaźnik do widgeta dla danej klasy
     @param
      parent - przekazywany dalej do klasy SettingsUnitsView, określa rodzica okna
   */
    explicit SettingsUnitsController(QWidget *parent = 0);
    ~SettingsUnitsController();
  /**
   Metoda publiczna zwracająca wskaźnik do interfejsu graficznego aktualnego widgeta
  */
    SettingsUnitsView *getView();
    void setModel(QString currentValue = "");
    UnitModel *getModel();

public slots:
  /**
   Slot publiczny ładujący dane o przeglądanej jednostce z bazy danych do odpowiednich lineEdit,
   ustawia także te lineEdit na disable
  */
    void showUnit();
  /**
   Slot publiczny określający rozpoczęcie definiowania nowej jednostki miary, ustawia wszystkie lineEdit na
   enable
 */
    void addUnit();
  /**
   Slot publiczny określający rozpoczęcie edycji odpowiedniej jednostki miary, ustawia wszystkie lineEdit na
   enable
 */
    void editUnit();
  /**
    Slot publiczny określający ustawienie danej jednostki jako nieaktywnej dla programu, taka jednostka jednak
    znajduje się w bazie z wartościa isActive równą zeru
  */
    void deleteUnit();
  /**
    @see showUnits()
   Slot publiczny zapisujący dane o nowej jednostce miary, bądź edytwanej jednostce, wywołuje slot showUnits()
 */
    void saveUnit();

};

#endif // SETTINGSUNITSCONTROLLER_H
