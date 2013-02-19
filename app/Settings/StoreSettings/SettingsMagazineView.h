#ifndef SETTINGSMAGAZINEVIEW_H
#define SETTINGSMAGAZINEVIEW_H

#include <QWidget>
#include <QScrollArea>
#include <QGridLayout>
#include <QPushButton>
#include <QInputDialog>
#include "Other/Warehouse/Warehouse.h"
#include "Other/Warehouse/WarehouseService.h"
#include "Database/Database.h"
#include "SettingsMagazineController.h"
#include "SettingsMagazineItemController.h"
class SettingsMagazineController;

/**
  @author Janiu
  Klasa widgeta zawierającego elementy dla ustawień magazynów
  */

class SettingsMagazineView : public QWidget
{
    Q_OBJECT
private:
    SettingsMagazineController *controller;
    QGridLayout *mainLayout;
    QGridLayout *warehousesLayout;
    WarehouseService *warehouseService;

   /**
    * Wektor zawierający dane o istniejących w bazie magazynach
    */
    QVector<Warehouse> warehouses;
   /**
    * Widgety zawierające dane o poszczegolnych magazynach
    */
    SettingsMagazineItemController **items;
   /**
    * Przycisk dodawania nowego magazynu
    */
    QPushButton *addNewStore;
   /**
    * Widget zawierający itemy (SettingsMagazineItem)
    */
    QWidget *warehousesList;
   /**
    ScrollArea dla widgeta storesList
    */
    QScrollArea *scrollArea;
   /**
    * Liczba całkowita zawierająca dane o ilosci aktualnie istniejacych magazynow
    */
    int itr;

public:
   /**
    * Konstruktor inicjujący wszystkie elementy dla danego widgeta
    * @param
    * parent - wskaźnik określający rodzica widgeta, wykorzystywany w programie
    * controller - wskaźnik do obiektu zawierającego kontrolki dla atrybutów danej klasy
    */
    explicit SettingsMagazineView(SettingsMagazineController *controller, QWidget *parent = 0);
    ~SettingsMagazineView();
   /**
    * Metoda ustawiająca widgety okna w odpowiednich miejscach layoutu
    */
    void initGraph();
   /**
    * Metoda wstawiająca/aktualizujaca itemy w storesList
    */
    void setItems();
   /**
    * @see setItems
    * Metoda ktora usuwa elementy znajdujące się w storesList wraz z storeList i jego layoutem
    */
    void deleteWidgets();

    QVector<Warehouse> getWarehouses();
    void setWarehouses(QVector<Warehouse> warehouses);
    int getIterator();
    SettingsMagazineItemController **getItems();

 signals:
   /**
    * Sygnal emitowany gdy zmieni sie liczba magazynow w bazie
    */
    void numberOfMagazinesChanged();

};

#endif // SETTINGSMAGAZINEVIEW_H
