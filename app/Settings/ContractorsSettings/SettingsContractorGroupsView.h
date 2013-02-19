#ifndef SETTINGSCONTRACTORGROUPSVIEW_H
#define SETTINGSCONTRACTORGROUPSVIEW_H

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
#include "SettingsContractorGroupsController.h"
#include "Settings/SettingsAbstractItemView.h"
class SettingsContractorGroupsController;
/**
  @author Janiu
  Klasa widgeta zawierającego elementy ustawień dla grup kontrahentów i dóbra
  */

class SettingsContractorGroupsView : public SettingsAbstractItemView
{
    Q_OBJECT

private:

    void initGraphicElements();
    void setGraphicSettings();
    void setInterfaceController();
    /**
      Wskaźnik do klasy zawierającej wszystkie kontrolki dla elementów badanego widgeta
    */
      SettingsContractorGroupsController *controller;

protected:
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
    Button *pushRepaint;

public:
  /**
    Konstruktor inicjujący wszystkie elementy dla danego widgeta
    @param
    parent - wskaźnik określający rodzica widgeta, wykorzystywany w programie
    controller - wskaźnik do obiektu zawierającego kontrolki dla atrybutów danej klasy
  */
    explicit SettingsContractorGroupsView(SettingsContractorGroupsController *controller, QWidget *parent = 0);
  /**
    Destruktor dla danej klasy, usuwa smodele
   */
    ~SettingsContractorGroupsView();
  /**
    Gettery i settery dla atrybutów danej klasy - nazwy analogiczne do nazw atrybutów
   */
    QComboBox *getBoxGroup();
    QLineEdit *getLineName();
    Button *getPushSave();
    Button *getPushEdit();
    Button *getPushDelete();
    Button *getPushNew();
  /**
    Metoda która zwraca nam widget z interfejsem dla określania cech danych grup dóbr
    */
    QFrame *createTablesInterface();
};
#endif // SETTINGSCONTRACTORGROUPSVIEW_H
