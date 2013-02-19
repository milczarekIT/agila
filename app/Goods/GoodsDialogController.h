#ifndef GOODSDIALOGCONTROLLER_H
#define GOODSDIALOGCONTROLLER_H

#include <QWidget>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QFileDialog>
#include <QMessageBox>
#include "Goods/GoodsDialogView.h"
#include "Goods/FeatureModel.h"
#include "Components/AddGroup.h"
#include "Components/InsertTextDialog.h"
#include "Database/Database.h"
#include "Other/TableStateManager.h"
#include "Components/MessageBox.h"
#include "Goods/GoodsValidator.h"
#include "Goods/GoodsService.h"
#include "Other/Preferences/SettingsPreferencesService.h"
class GoodsDialogView;
class GoodsValidator;

/**
  @author Janiu
  Klasa odpowiedzialna za nadanie kontrolek okienku dialogowemu dodawania i edytowania kontrahentów.
  */
class GoodsDialogController : public QWidget
{
    Q_OBJECT

private:
    GoodsDialogView *view;
    GoodsValidator *validator;
    GoodsService *service;
    TaxModel *taxModel;
    UnitModel *unitModel;
    GoodsGroupModel *goodsGroupModel;
    TableStateManager* tableStateManager;
    FeatureModel *featureModel;
    SettingsPreferencesService *settingsPreferences;

    /**
       Pole przechowujące grupę aktualnie edytowanego tow./usługi. 0 gdy dodawanie nowego.
       */
   int goodGroupVal;
   Goods good, oldGood;

   /** inicjuje OldGood, np. pobiera domyślnie ustawiony tax itp **/
   void initOldGood();
   /**
     kopiuje wybrane zdjęcie do folderu programu
     */
   void copyPhotoToProgramDir ();
    /**
    pobiera dane z okienka
    */
    Goods getGoodData();

    /**
    * Metoda zwracająca true, jeśli w formularzu nastąpiły zmiany, lub false gdy brak zmian
    */
    bool isChangesOccured();

    /**
    pobiera cechy
    */
    QVector<Feature> getGoodFeatures();
    QStandardItemModel *model;
    bool autoSymbol;
    bool priceCalculatingEnabled;
     /**
       Liczba rzeczywista zawierająca informacje o aktualnie wybranej stawce VAT
     */
    double tax;

    /**
      * Inicjalizacja cen przy edycji
      */
    void initPricesInEdit();

    void fillBox (QComboBox *box,QVector<Tax> values);
    void fillBox (QComboBox *box,QVector<GoodsGroup> values);
    void setPriceTableItem(int row, int col, double value); // milczu
    void calculatePriceGrossFromNetForLevel(int row); // liczy cenę brutto na podstawie netto
    void calculatePriceNetFromGrossForLevel(int row); // liczy cenę netto na podstawie brutto
    void calculatePriceNetFromMarginForLevel(int row); // liczy cenę netto na podstawie narzutu
    void calculatePriceGrossFromDiscountForLevel(int row); // liczy cenę brutto na podstawie upustu
    void calculatePriceMagByMarginA(); // liczy cenę zakupu, na podstawie ceny netto A i narzutu
    void updateDiscontOrPriceForLevelBC(); // zaktualizuj wysokość upustów dla cen B,C przy zmianie A
    bool isPriceNetGrossSet(int row); // sprawdza czy cena netto, brutto ustawiona (tzn. inna niż 0,00)
    void calculateAllPricesGross(); // wyliczenie cen A,B,C bruto na podstawie netto

    void setPriceMag(double value);
    void setDefaultMargins();
    void restoreTableState();
    void saveTableState();

    bool isAddingOnlyToActualWarehouse(); // tylko dla dodawnia nowego towaru
public:
    explicit GoodsDialogController(QWidget *parent);
    ~GoodsDialogController();


  /**
    Pobiera od użytkownika dane nowego towaru/usługi i dodaje go do bazy.
    @returns true jeżeli dodano nowy towar/usługę false jeżeli nie.
    */
    bool exec();
    /**
      Edycja towaru/uslugi o podanym id.
      @returns true jeżeli dokonano edycji false jeżeli nie.
      */
      bool exec (int id);

    GoodsDialogView* getView();

public slots:

     /**
       Slot wywołujący okienko dialogowe wpisywania tekstu w celu dodania nowej grupy dóbr
       do bazy danych
       @see dialogTaxesAccess()
      */
        void dialogGoodsGroup();

        /**
          * Po naciśnieciu 'Anuluj', sprawdza czy nie nastąpiły zmiany i czy użytkownik chce zapisać
          */
        void checkChanges();
        void addTax();
        void removeTax();
        void calculatePrices(QTableWidgetItem *item);
        void calculateAllPricesFromMag();
        void calculatePricesMagNet(int row);
        void calculatePricesMagGross(int row);
        void calculateMarginFromPrice(int row);
        void calculateDiscountFromPrice(int row);

private slots:

 /**
   Slot publiczny umożliwiający usunięcie danej grupy dóbr z bazy danych
 */
    void deleteGoodsGroup ();

    /**
   Slot publiczny, który przelicza wartości netto na brutto podczas zmiany stawki VAT w combo boxie
 */
    void calculatePricesForTax(int index);
    /**
      Slot umozliwia update widoku cech w momencie gdy wybrano inna grupę
      */
    /**
      generuje model tabelki do wpisywania wartosci konkretnych cech
      */
    void updateFeatureModel(int index);
    /**
      Obsługa funkcjonalności zdjęcia
      */
    void fotoMenuAcces ( QAction * action);
    /**
      Slot publiczny wywoływany gdy jest wprowadzany test do pola nazwa
      */
      void nameTyping (const QString & text );
      /**
        Slot publiczny wywoływany podczas wpisywania danych do pola symbol. Sprawdza czy jest potrzeba automatycznego
        uzupełniania pola Symbol.*/
      void checkAutoSymbol (const QString & text );
      /**
        Slot publiczny wykorzystywany do sprawdzenia czy podano minimalną ilość danych
        */
     void checkRequredFields();


};

#endif // GOODSDIALOGCONTROLLER_H
