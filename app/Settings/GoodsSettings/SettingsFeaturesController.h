#ifndef SETTINGSFEATURESCONTROLLER_H
#define SETTINGSFEATURESCONTROLLER_H

#include <QWidget>
#include "Goods/Feature.h"
#include "Database/Database.h"
#include "Goods/FeatureModel.h"
#include "Components/MessageBox.h"
#include "SettingsFeaturesView.h"
#include "Settings/SettingsAbstractItemController.h"
class SettingsFeaturesView;

 /**
  @author Janiu
  Klasa odpowiedzialna za nadanie kontrolek zakładce ustawień cech towarowych dla tabWidgetSettings.
  */
class SettingsFeaturesController : public SettingsAbstractItemController
{
    Q_OBJECT
  /**
   QWidget z gama elementów służącą do ustawień cech towarowych, wykorzystywany do nadania mu odpowiedniej funkcjonalności
  */
   SettingsFeaturesView *view;
   /**
     Wskaźnik do klasy określającej kwereny dla grup, wykorzystywane do komunikacji z baza danych
   */
   FeatureModel *featureModel;
   void fillBox(QComboBox *box,QVector<Feature> values);
   bool checkFillInTheFields();

public:
  /**
    Konstruktor inicjujący wskaźnik do widgeta dla danej klasy
    @param
     parent - przekazywany dalej do klasy SettingsFeaturesView, określa rodzica okna
  */
    explicit SettingsFeaturesController(QWidget *parent = 0);
    ~SettingsFeaturesController();
  /**
   Metoda publiczna zwracająca wskaźnik do interfejsu graficznego aktualnego widgeta
  */
    SettingsFeaturesView *getView();
    FeatureModel *getModel();
    void setModel(QString currentValue = "");

public slots:
  /**
   Slot publiczny ładujący dane o przeglądanej cesze z bazy danych do odpowiednich lineEdit,
   ustawia także te lineEdit na disable
  */
    void showFeatures();
  /**
   Slot publiczny określający rozpoczęcie definiowania nowej cechy towarowej, ustawia wszystkie lineEdit na
   enable
 */
    void addFeature();
  /**
   Slot publiczny określający rozpoczęcie edycji odpowiedniej cechy towarowej, ustawia wszystkie lineEdit na
   enable
 */
    void editFeature();
  /**
    Slot publiczny określający ustawienie danej cechy towarowej jako nieaktywnej dla programu, taka cecha jednak
    znajduje się w bazie z wartościa isActive równą zeru
  */
    void deleteFeature();
  /**
    @see showFeatures()
   Slot publiczny zapisujący dane o nowej cesze miary, bądź edytwanej jednostce, wywołuje slot showFeatures()
 */
    void saveFeature();
};

#endif // SETTINGSFEATURESCONTROLLER_H
