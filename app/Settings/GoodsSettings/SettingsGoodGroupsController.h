#ifndef SETTINGSGOODGROUPSCONTROLLER_H
#define SETTINGSGOODGROUPSCONTROLLER_H

#include <QWidget>
#include "Database/Database.h"
#include "Goods/FeatureModel.h"
#include "Components/MessageBox.h"
#include "SettingsGoodGroupsView.h"
#include "Settings/SettingsTVModel.h"
#include "Settings/SettingsAbstractItemController.h"
class SettingsGoodGroupsView;

/**
  @author Janiu
  Klasa odpowiedzialna za nadanie kontrolek zakładce ustawień grup kontrahenckich i dóbr dla tabWidgetSettings.
  */
class SettingsGoodGroupsController : public SettingsAbstractItemController
{
    Q_OBJECT

private:
    SettingsGoodGroupsView *view;

    SettingsTVModel *featureTVModel;
    SettingsTVModel *featureForRestTVModel;
    FeatureModel *featureModel;
    FeatureModel *featureForRestModel;
    GoodsGroupModel *goodsGroupModel;
    void fillBox(QComboBox *box,QVector<GoodsGroup> values);
    bool checkFillInTheFields();

public:
  /**
   Konstruktor inicjujący wskaźnik do widgeta dla danej klasy
  @param
    parent - przekazywany dalej do klasy SettingsGoodGroupsView, określa rodzica okna
   @see chooseKindOfGroups();
 */
    explicit SettingsGoodGroupsController(QWidget *parent = 0);
    ~SettingsGoodGroupsController();
  /**
   Metoda publiczna zwracająca wskaźnik do interfejsu graficznego aktualnego widgeta
  */
    SettingsGoodGroupsView *getView();
  /**
    Metoda publiczna ładująca modele danych z bazy do tabel
   */
    void setTables(int groupId);
    void setModel(QString currentValue = "");
    FeatureModel *getFeatureModel();
    FeatureModel *getFeatureForRestModel();
    GoodsGroupModel *getGoodsGroupModel();
    void setTablesModel();

public slots:
  /**
    Slot publiczny który określa co sie stanie gdy z boxGroup wybierzemy jakąś grupę, a mianowicie, lineEdit ustawi się na disable
    oraz załaduję się do niego nazwa grupy, w przypadku grup dobr dochodzi takze do przeladowania tableFeatures
    */
    void chooseGroup();
  /**
   Slot publiczny określający rozpoczęcie edycji odpowiedniej grupy, ustawia lineEdit na
   enable
 */
    void editGroup();
  /**
   Slot publiczny określający rozpoczęcie definiowania nowej grupy, ustawia lineEdit na
   enable
 */
    void newGroup();
  /**
   @see chooseKindOfGroups();
   Slot publiczny ustawiający grupe niedostępną dla programu, pozostaje tylko w bazie
 */
    void deleteGroup();
  /**
    @see chooseKindOfGroups();
   Slot publiczny zapisujący dane o nowej grupie, bądź edytwanej grupie
 */
    void saveGroup();
  /**
    Slot publiczny który dodaje dla danej grupy towarowej wybrana ceche
    */
    void addFeature();
  /**
    Slot publiczny który usuwa wybrana ceche dla danej grupy towarowej
    */
    void deleteFeature();


};

#endif // SETTINGSGOODGROUPSCONTROLLER_H
