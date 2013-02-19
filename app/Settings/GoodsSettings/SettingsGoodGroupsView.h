#ifndef SETTINGSGOODGROUPSVIEW_H
#define SETTINGSGOODGROUPSVIEW_H

#include <QLabel>
#include <QFrame>
#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QGridLayout>
#include <QRadioButton>
#include "Goods/GoodsGroup.h"
#include "Database/Database.h"
#include "Components/Button.h"
#include "Components/TableView.h"
#include "Other/SimpleStructure.h"
#include "SettingsGoodGroupsController.h"
#include "Settings/SettingsAbstractItemView.h"
class SettingsGoodGroupsController;
/**
  @author Janiu
  Klasa widgeta zawierającego elementy ustawień dla grup kontrahentów i dóbra
  */

class SettingsGoodGroupsView : public SettingsAbstractItemView
{
    Q_OBJECT

private:
  /**
    Wskaźnik do klasy zawierającej wszystkie kontrolki dla elementów badanego widgeta
  */
    SettingsGoodGroupsController *controller;
  /**
    ComboBox który zawiera nazwy grup dóbr lub kontrahentów, dzięki niemu można wyświetlić dane o kontkretnej grupie
 */
    QComboBox *boxGroup;
  /**
     Pole, w którym umieszczamy nazwę danej grupy, wykorzystywane do umieszczenia danych w bazie danych,
     bądź modyfikacji istniejącch informacji o grupie
  */
    QLineEdit *lineName;
  /**
    Tabela zawierająca nazwy wszystkich cech grup dóbr zawartych w bazie danych, umożliwia do nich dostęp
   */
    TableView *tableFeatures;
  /**
    Tabela zawierająca nazwy wszystkich cech dla danego dobra zawartych w bazie danych, umożliwia do nich dostęp
   */
    TableView *tableGGFeatures;
  /**
    Przycisk umożliwiający zapisanie w bazie danych dokonanych zmian
   */
    Button *pushSave;
  /**
    Przycisk umożliwiający edycję wybranej grupy
   */
    Button *pushEdit;
  /**
    Przycisk umożliwiający ustawienie danej grupy jako nieaktywnej, zostaje tylko w bazie
   */
    Button *pushDelete;
  /**
    Przycisk umożliwiający dodanie nowej grupy
   */
    Button *pushNew;
  /**
    Przycisk umożliwiający dodanie cechy dla danej grupy dóbr z całej listy cech
    */
    Button *pushAddFeatures;
  /**
    Przycisk umożliwiający usunięcie cechy z listy cech danej grupy
    */
    Button *pushDelFeatures;
  /**
    Widget w którym zostały umieszczone elementy interfejsu dla określania cech danej grupy dóbr
    */
    QFrame *tablesInterface;
    void initGraphicElements();
    void setGraphicSettings();
    void setInterfaceController();


public:
  /**
    Konstruktor inicjujący wszystkie elementy dla danego widgeta
    @param
    parent - wskaźnik określający rodzica widgeta, wykorzystywany w programie
    controller - wskaźnik do obiektu zawierającego kontrolki dla atrybutów danej klasy
  */
    explicit SettingsGoodGroupsView(SettingsGoodGroupsController *controller, QWidget *parent = 0);
  /**
    Destruktor dla danej klasy, usuwa smodele
   */
    ~SettingsGoodGroupsView();
  /**
    Gettery i settery dla atrybutów danej klasy - nazwy analogiczne do nazw atrybutów
   */
    QComboBox *getBoxGroup();
    QLineEdit *getLineName();
    TableView *getTableFeatures();
    TableView *getTableGGFeatures();
    QRadioButton *getBoxGoodsGroups();
    QRadioButton *getBoxContractorsGroups();
    Button *getPushSave();
    Button *getPushEdit();
    Button *getPushDelete();
    Button *getPushNew();
    Button *getPushAddFeatures();
    Button *getPushDelFeatures();
    QFrame *getTablesInterface();
  /**
    Metoda która zwraca nam widget z interfejsem dla określania cech danych grup dóbr
    */
    QFrame *createTablesInterface();
};

#endif // SETTINGSGOODGROUPSVIEW_H
