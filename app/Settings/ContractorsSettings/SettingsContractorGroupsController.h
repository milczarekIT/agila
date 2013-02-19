#ifndef SETTINGSCONTRACTORGROUPSCONTROLLER_H
#define SETTINGSCONTRACTORGROUPSCONTROLLER_H

#include <QWidget>
#include "Database/Database.h"
#include "Goods/FeatureModel.h"
#include "Components/MessageBox.h"
#include "SettingsContractorGroupsView.h"
#include "Settings/SettingsAbstractItemController.h"
class SettingsContractorGroupsView;

/**
  @author Janiu
  Klasa odpowiedzialna za nadanie kontrolek zakładce ustawień grup kontrahenckich i dóbr dla tabWidgetSettings.
  */
class SettingsContractorGroupsController : public SettingsAbstractItemController
{
    Q_OBJECT

private:
    ContractorGroupModel *contractorGroupModel;
    void fillBox(QComboBox *box,QVector<ContractorGroup> values);
    bool checkFillInTheFields();
    /**
    QWidget z gama elementów służącą do ustawień grup, wykorzystywany do nadania mu odpowiedniej funkcjonalności
    */
    SettingsContractorGroupsView *view;

public:
  /**
   Konstruktor inicjujący wskaźnik do widgeta dla danej klasy
  @param
    parent - przekazywany dalej do klasy SettingsContractorGroupsView, określa rodzica okna
   @see chooseKindOfGroups();
 */
    explicit SettingsContractorGroupsController(QWidget *parent = 0);
    ~SettingsContractorGroupsController();

    ContractorGroupModel *getContractorGroupModel();
    SettingsContractorGroupsView *getView();

public slots:
    void setModel(QString currentValue = "");
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

};


#endif // SETTINGSCONTRACTORGROUPSCONTROLLER_H
