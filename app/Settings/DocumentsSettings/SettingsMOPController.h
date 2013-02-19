#ifndef SETTINGSMOPCONTROLLER_H
#define SETTINGSMOPCONTROLLER_H

#include <QWidget>
#include "Document/MOPModel.h"
#include "Database/Database.h"
#include "Components/MessageBox.h"
#include "SettingsMOPView.h"
#include "Settings/SettingsAbstractItemController.h"
class SettingsMOPView;

/**
  @author Janiu
  Klasa odpowiedzialna za nadanie kontrolek zakładce ustawień metod płatności dla tabWidgetSettings.
  */
class SettingsMOPController : public SettingsAbstractItemController
{
    Q_OBJECT
 private:
 /**
   QWidget z gama elementów służącą do ustawień sposobów płatności, wykorzystywany do nadania mu odpowiedniej funkcjonalności
  */
   SettingsMOPView *view;
   void fillBox(QComboBox *box,QVector<MethodOfPayment> values);
   /**
    Wskaźnik do klasy określającej kwereny dla sposobów płatności, wykorzystywane do komunikacji z baza danych
   */
   MOPModel *mopModel;
   bool checkFillInTheFields();

 public:
 /**
    Konstruktor inicjujący wskaźnik do widgeta dla danej klasy
    @param
     parent - przekazywany dalej do klasy SettingsMOPView, określa rodzica okna
  */
   explicit SettingsMOPController(QWidget *parent = 0);
   ~SettingsMOPController();
   /**
   Metoda publiczna zwracająca wskaźnik do interfejsu graficznego aktualnego widgeta
  */
   SettingsMOPView *getView();
   void setModel(QString currentValue = "");
   MOPModel *getModel();

  public slots:
   /**
    Slot publiczny ładujący dane o przeglądanym sposobie płatności z bazy danych do odpowiednich widgetów,
    ustawia te widgety także na disable
   */
    void showMOPs();
   /**
    Slot publiczny określający rozpoczęcie definiowania nowego sposobu płatności, ustawia lineName i spinNumberofDays na
    enable
   */
    void addMOP();
   /**
    Slot publiczny określający rozpoczęcie edycji odpowiedniego sposobu płatności, ustawia lineName i spinNumberofDays na
    enable
   */
    void editMOP();
   /**
     Slot publiczny określający ustawienie danego sposobu płatności jako nieaktywnego dla programu, taki sposób jednak
     znajduje się w bazie z wartościa isActive równą zeru
   */
    void deleteMOP();
   /**
     @see showMOPs()
     Slot publiczny zapisujący dane o nowym sposobie płatności, bądź edytwanym sposobiee, wywołuje slot showMOPs()
   */
    void saveMOP();

};

#endif // SETTINGSMOPCONTROLLER_H
