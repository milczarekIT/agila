#ifndef SETTINGSMAGAZINEITEMVIEW_H
#define SETTINGSMAGAZINEITEMVIEW_H

#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>
#include <QRadioButton>
#include "Other/Warehouse/Warehouse.h"
#include "Other/Warehouse/WarehouseService.h"
#include "SettingsMagazineItemController.h"
class SettingsMagazineItemController;

/**
  @author Janiu
  Klasa widgeta/itemu zawierającego elementy dla ustawień danego magazynu
  */

class SettingsMagazineItemView : public QFrame
{
    Q_OBJECT
private:
   /**
    * Wskaźnik do klasy zawierającej wszystkie kontrolki dla elementów badanego widgeta
    */
    SettingsMagazineItemController *controller;
   /**
    * Główny layout aktualnego widgeta, służący do ułożenia elementów dotyczących ustawień dla jednostek miary
    */
    QGridLayout *mainLayout;
   /**
    * Model bazy danych zawierający kwerendy pozwalające na dodawanie/ usuwanie oraz zmiane magazynow
    */
    WarehouseService *service;
    Warehouse warehouse;

    QLineEdit *warehouseShortName;
    QLineEdit *warehouseName;
   /**
    * Label wyświetlający nazwę dla danego itemu
    */
    QLabel *widgetValue;
   /**
    * Przycisk, dzięki któremu możemy usunąć dany magazyn
    */
    QPushButton *deleteStore;
    QPushButton *editWarehouse;
   /**
    * CheckBox, który mówi o tym czy dany magazyn jest aktualnie działającym czy też nie
    */
    QLabel *labelDefautWarehouse;

public:
   /**
    * Konstruktor inicjujący wszystkie elementy dla danego widgeta
    * @param
    * model - zawiera kwerendy do bazy danych dotyczące ustawień magazynów
    * warehouse - struktura zawierająca cechy danego magazynu
    * parent - wskaźnik określający rodzica widgeta, wykorzystywany w programie
    * controller - wskaźnik do obiektu zawierającego kontrolki dla atrybutów danej klasy
    */
    explicit SettingsMagazineItemView(WarehouseService *service, Warehouse warehouse,SettingsMagazineItemController *controller, QWidget *parent = 0);
   /**
    * Metoda ustawiająca widgety okna w odpowiednich miejscach layoutu
    */
    void initGraph();
   /**
    * Metoda ingerująca w ustawienia layoutu oraz stan i wygląd widgetów
    */
    void setGraphSettings();
   /**
    * @see
    *  editWarehouse()
    *  emitDeleteSignal()
    *  emitCheckSignal()
    * Metoda nadająca kontrolę odpowiednim widgetom w module
    */
    void setInterfaceController();

    QLabel *getLabelDefaultWarehouse();
    Warehouse getWarehouse();
    QLineEdit *getWarehouseName();
    QLineEdit *getWarehouseShortName();
    QLabel *getWidgetValue();
    void setWarehouse(Warehouse warehouse);

};

#endif // SETTINGSMAGAZINEITEMVIEW_H
