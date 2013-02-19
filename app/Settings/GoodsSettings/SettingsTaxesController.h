#ifndef SETTINGSTAXESCONTROLLER_H
#define SETTINGSTAXESCONTROLLER_H

#include <QWidget>
#include "Goods/TaxModel.h"
#include "Database/Database.h"
#include "Components/MessageBox.h"
#include "SettingsTaxesView.h"
#include "Settings/SettingsAbstractItemController.h"
#include "Other/Preferences/SettingsPreferencesService.h"
class SettingsTaxesView;

/**
  @author Janiu
  Klasa odpowiedzialna za nadanie kontrolek zakładce ustawień stawek VAT dla tabWidgetSettings.
  */
class SettingsTaxesController : public SettingsAbstractItemController
{
    Q_OBJECT

private:
  /**
  QWidget z gama elementów służącą do ustawień stawek VAT, wykorzystywany do nadania mu odpowiedniej funkcjonalności
  */
    SettingsTaxesView *view;
  /**
    Wskaźnik do klasy określającej kwereny dla stawek VAT, wykorzystywane do komunikacji z baza danych
   */
    TaxModel *taxModel;
    SettingsPreferencesService* preferences;
    void setItemForValue(QString value);
    bool checkFillInTheFields();

public:
  /**
   Konstruktor inicjujący wskaźnik do widgeta dla danej klasy
  @param
    parent - przekazywany dalej do klasy SettingsTaxesView, określa rodzica okna
 */
    SettingsTaxesController(QWidget *parent = 0);
    ~SettingsTaxesController();
  /**
   Metoda publiczna zwracająca wskaźnik do interfejsu graficznego aktualnego widgeta
  */
    SettingsTaxesView *getView();
    TaxModel *getModel();
  /**
    @see createItem()
    Metoda wywołująca createItem(), pobierająca na nowo dane  bazy do wektora taxes i ładująca dane do tabeli - na nowo
   */
    void updateTable();

public slots:
    void setModel(QString currentValue = "");
  /**
   Slot publiczny ładujący dane o przeglądanej stawce vat z bazy danych do odpowiednich lineEdit,
   ustawia także te lineEdit na disable
 */
    void setData();
    void setTaxIdData();
  /**
   Slot publiczny określający rozpoczęcie edycji odpowiedniej stawki VAT, ustawia lineName i lineSign na
   enable
 */
    void editTax();
  /**
   Slot publiczny określający rozpoczęcie definiowania nowej stawki VAT, ustawia wszystkie lineEdit na
   enable
 */
    void newTax();
  /**
    @see setData()
   Slot publiczny zapisujący dane o nowej stawce VAT, bądź edytwanej stawce, wywołuje slot setData()
 */
    void saveTax();
  /**
   Slot publiczny zmieniający w bazie danych zmienną active_in_app w momencie kiedy zaznaczymy bądź odznaczymy
   checkboxa w tabeli przy odpowiedniej stawce
 */
    void changeActivate();
  /**
   Slot publiczny ustawiający stawkę VAT niedostępną dla programu, pozostaje tylko w bazie
 */
    void deleteTax();
  /**
   Slot publiczny uniemożliwiający wybrania przy edycji i definiowaniu pola Stawka zw. z QComboBoxa
 */
    void enableRateNull();
    void signGenerating(const QString value);

};

#endif // SETTINGSPANELCONTROLLER_H
