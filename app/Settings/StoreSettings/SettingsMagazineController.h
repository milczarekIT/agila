#ifndef SETTINGSMAGAZINECONTROLLER_H
#define SETTINGSMAGAZINECONTROLLER_H

#include <QWidget>
#include "Components/MessageBox.h"
#include "Other/Warehouse/WarehouseModel.h"
#include "Settings/StoreSettings/WarehouseDialogController.h"
#include "SettingsMagazineView.h"
class SettingsMagazineView;

/**
  @author Janiu
  Klasa widgetu zawierającego elementy dla ustawień magazynow
  */

class SettingsMagazineController : public QWidget
{
    Q_OBJECT
private:
  /**
   * QWidget z gama elementów służącą do ustawień jednostek miary, wykorzystywany do nadania mu odpowiedniej funkcjonalności
   */
   SettingsMagazineView *view;
   WarehouseService *warehouseService;
  /**
   * MessageBox ktory wyswietla uzytkownikowi informacje badz zapytanie o dokonanie operacji
   */
   MessageBox *messageBox;

public:
   /**
    * Konstruktor inicjujący wskaźnik do widgeta dla danej klasy
    * @param
    *   parent - przekazywany dalej do klasy SettingsUnitsView, określa rodzica okna
    */
    explicit SettingsMagazineController(QWidget *parent = 0);
   ~SettingsMagazineController();
   /**
    * Metoda publiczna zwracająca wskaźnik do interfejsu graficznego aktualnego widgeta
    */
    SettingsMagazineView *getView();


public slots:
    void addWarehouse();
    void editWarehouse(int id);
    void removeWarehouse(int id);

   /**
    * Slot emitujący sygnał magazineChanged()
    * @see magazineChanged()
    */
    void emitMagazineChanged();

signals:
   /**
    * Sygnał wywoływany podczas zmiany ilości magazynów
    */
    void warehouseChanged();

};

#endif // SETTINGSMAGAZINECONTROLLER_H
