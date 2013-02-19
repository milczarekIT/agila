#ifndef SETTINGSPANELVIEW_H
#define SETTINGSPANELVIEW_H

#include <QWidget>
#include <QListWidget>
#include <QStackedLayout>
#include "SettingsPanelController.h"
#include "Settings/GoodsSettings/SettingsPricesController.h"
#include "Settings/OtherSettings/SettingsUserController.h"
#include "Settings/OtherSettings/SettingsPrintController.h"
#include "Settings/OtherSettings/SettingsOwnerController.h"
#include "Settings/GoodsSettings/SettingsTaxesController.h"
#include "Settings/GoodsSettings/SettingsUnitsController.h"
#include "Settings/DocumentsSettings/SettingsMOPController.h"
#include "Settings/OtherSettings/SettingsOutlookController.h"
#include "Settings/StoreSettings/SettingsMagazineController.h"
#include "Settings/GoodsSettings/SettingsFeaturesController.h"
#include "Settings/StoreSettings/SettingsTransportController.h"
#include "Settings/GoodsSettings/SettingsGoodGroupsController.h"
#include "Settings/GoodsSettings/SettingsMassTaxesChangeController.h"
#include "Settings/DocumentsSettings/SettingsDocumentTextController.h"
#include "Settings/DocumentsSettings/SettingsDefaultDocPlaceController.h"
#include "Settings/DocumentsSettings/SettingsDocumentNumberingController.h"
#include "Settings/ContractorsSettings/SettingsContractorGroupsController.h"
#include "Settings/DocumentsSettings/SettingsPriceSelectionController.h"
class SettingsPanelController;

/**
  @author Janiu
  Klasa odpowiedzialna za zbudowanie wnętrza zakładki Ustawienia w głównym oknie programu
  */
class SettingsPanelView : public QWidget {
    Q_OBJECT

private:
  /**
    Layout potrzebny do dynamicznego dzialania interfejsu, zapewnia on interakcje pomiedzy lista
    a widgetami z ktorych tylko jeden jest widoczny w danej chwili
   */
    QStackedLayout *layout;
  /**
    Główny layout aktualnego widgeta, służący do ułożenia elementów dotyczących wszystkich modułów ustawień
   */
    QGridLayout *mainLayout;
  /**
    Wskaźnik do klasy zawierającej wszystkie kontrolki dla elementów badanego widgeta
  */
    SettingsPanelController *controller;
  /**
    Widget który buduje interfejs i jego obsługe dla modułu ustawień stawek VAT
  */
    SettingsTaxesController *tabVAT;
  /**
    Widget który buduje interfejs i jego obsługe dla modułu ustawień jednostek miary
  */
    SettingsUnitsController *tabUnits;
  /**
    Widget który buduje interfejs i jego obsługe dla modułu ustawień grup kontrahenckich i dóbr
  */
    SettingsContractorGroupsController *tabConGroups;
    SettingsGoodGroupsController *tabGoodGroups;
  /**
    Widget który buduje interfejs i jego obsługe dla modułu ustawień cech grup dóbr
  */
    SettingsFeaturesController *tabFeatures;
  /**
    Widget który buduje interfejs i jego obsługe dla modułu ustawień dla podmiotu
  */
    SettingsOwnerController *tabOwner;
  /**
    Widget który buduje interfejs i jego obsługe dla modułu ustawień dla podmiotu
  */
    SettingsMOPController *tabMOP;
  /**
    Widget który buduje interfejs i jego obsługe dla modułu ustawień dla tekstu pod dokumentem
  */
    SettingsDocumentTextController *tabDocumentText;
  /**
    Widget który buduje interfejs i jego obsługe dla modułu ustawień dla numeracji dokumentów
  */
    SettingsDocumentNumberingController *tabDocumentNumbering;
   /**
     Widget który buduje interfejs i jego obsługe dla modułu ustawień dla numeracji dokumentów
   */
    SettingsPricesController* tabPrices;
    SettingsMagazineController *tabMagazine;
    SettingsPriceSelectionController* tabPricesSelection;
    SettingsPrintController *tabPrint;
    SettingsOutlookController *tabOutlook;
    SettingsDefaultDocPlaceController *tabDefDocPlace;
    SettingsMassTaxesChangeController *tabMassTaxesChange;
    SettingsUserController *tabUser;
    SettingsTransportController *tabTransport;

    QListWidget *list;
    QTabWidget *goodsTabWidget;
    QTabWidget *documentsTabWidget;
    QTabWidget *usersTabWidget;
    QTabWidget *storeTabWidget;
    void createGoodsTabs();
    void createDocumentsTabs();
    void createStoreTabs();
    void setInterfaceController();
    void setGraphicElements(QWidget *parent = 0);
    void setGraphicSettings();
    void demoBlocker();
    void createAction();
    void setConnctions();


    QAction * action;
    QAction * action2;

public:
  /**
    Konstruktor który zawiera wszystkie elementy aktualnego tabWidgeta
    @param
    parent - wskaźnik określający rodzica widgeta, wykorzystywany w programie
    controller - wskaźnik do obiektu zawierającego kontrolki dla atrybutów danej klasy
  */
    explicit SettingsPanelView(SettingsPanelController *controller, QWidget *parent = 0);
    ~SettingsPanelView();

  /**
    Metoda, która tworzy listę, której elementami są nazwy wszystkich modułów ustawień, stanowi ona
    żródło interakcji pomiędzy nimi
    @see
    createListWidgetItem()
   */
    void createListWidget();
  /**
    Metoda, która tworzy itemy/elementy dla tworzonej listy
   */
    QListWidgetItem *createListWidgetItem(QString value);
  /**
    Getter dla modułu ustawień grup kontrahenckich i dóbr
    */
    SettingsMagazineController *getTabMagazine();
    SettingsTaxesController *getTabVAT();
    SettingsUnitsController *getTabUnits();
    SettingsContractorGroupsController *getTabConGroups();
    SettingsGoodGroupsController *getTabGoodGroups();
    SettingsFeaturesController *getTabFeatures();
    SettingsOwnerController *getTabOwner();
    SettingsMOPController *getTabMOP();
    SettingsDocumentTextController *getTabDocumentText();
    SettingsDocumentNumberingController *getTabDocumentNumbering();
    SettingsPrintController *getTabPrint();
    SettingsDefaultDocPlaceController *getTabDefDocPlace();
    SettingsMassTaxesChangeController *getTabMassTaxesChange();
    SettingsUserController *getTabUser();
    SettingsTransportController *geTabTransport();
    SettingsOutlookController *getTabOutlook();
    TableView *getTableView();
    QTabWidget *getGoodsTabWidget();
    QTabWidget *getDocumentsTabWidget();
    QTabWidget *getStoreTabWidget();
    QListWidget *getList();

public slots:

    void swapFocus();

};

#endif
