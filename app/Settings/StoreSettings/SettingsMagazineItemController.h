#ifndef SETTINGSMAGAZINEITEMCONTROLLER_H
#define SETTINGSMAGAZINEITEMCONTROLLER_H

#include <QWidget>
#include "Components/MessageBox.h"
#include "SettingsMagazineItemView.h"
#include "Other/Warehouse/WarehouseService.h"
class SettingsMagazineItemView;

/**
  @author Janiu
  Klasa odpowiedzialna za nadanie kontrolek itemom dla SettingsMagazine
  */

class SettingsMagazineItemController : public QFrame
{
    Q_OBJECT
private:
   SettingsMagazineItemView *view;
  /**
   MessageBox ktory wyswietla uzytkownikowi informacje badz zapytanie o dokonanie operacji
  */
   MessageBox *messageBox;

public:
    explicit SettingsMagazineItemController(WarehouseService *service,Warehouse warehouse, QWidget *parent = 0);
    SettingsMagazineItemView *getView();

public slots:
   /**
    * Sloty wywolujace sygnaly w danej klasie, nazwy sa analogiczna
    */
    void emitEditSignal();
    void emitDeleteSignal();

signals:
    void removeButtonClicked(int warehouseId);
    void editButtonClicked(int warehouseId);
   /**
    * Sygnał zwracający id magazynu przy wciśnięciu checkboxa
    */
    void checkWarehouse(int id);

};

#endif
