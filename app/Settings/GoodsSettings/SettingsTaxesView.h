#ifndef SETTINGSTAXESVIEW_H
#define SETTINGSTAXESVIEW_H

#include <QLabel>
#include <QVector>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "Goods/Tax.h"
#include "Database/Database.h"
#include "Components/Button.h"
#include "SettingsTaxesController.h"
#include "Settings/SettingsAbstractItemView.h"
class SettingsTaxesController;

/**
  @author Janiu
  Klasa widgeta zawierającego elementy ustawień stawek VAT
  */
class SettingsTaxesView : public SettingsAbstractItemView
{
    Q_OBJECT
private:
  /**
    Wskaźnik do klasy zawierającej wszystkie kontrolki dla elementów badanego widgeta
  */
    SettingsTaxesController *controller;
  /**
    ComboBox który zawiera nazwy typów stawek VAT, można dzięki niemu dokonać wyboru pomiędzy stawką podstawową
    a stawką zw.
  */
    QComboBox *boxName;
  /**
    Pola, w których umieszczamy najważniejsze dane o stawce VAT, wykorzystywane do umieszczenia tych danych
    w bazie danych, bądź modyfikacji istniejącch informacji o stawce
  */
    QLineEdit *lineTaxForRR;
    QLineEdit *lineValue;
    QLineEdit *lineSign;
  /**
    Przycisk umożliwiający dodanie nowej stawki VAT
   */
    //Button *pushRepaint;
    Button *pushNew;
  /**
    Przycisk umożliwiający edycję wybranej stawki VAT
   */
    Button *pushEdit;
  /**
    Przycisk umożliwiający zapisanie w bazie danych dokonanych zmian
   */
    Button *pushSave;
  /**
    Przycisk umożliwiający ustawienie danej stawki VAT jako nieaktywnej, zostaje tylko w bazie
   */
    Button *pushDelete;
    QVector<Tax> taxes;
  /**
    Tabela zawierająca nazwy wszystkich stawek zawartych w bazie danych, umożliwia do nich dostęp,
    ładowane są do niej dane z wektora taxes
   */
    QTableWidget *tableTaxes;
    void initGraphicElements();
    void setGraphicSettings();
    void setInterfaceController();

public:
  /**
    Gettery i settery dla atrybutów danej klasy - nazwy analogiczne do nazw atrybutów
   */
    QLineEdit *getLineValue();
    QLineEdit *getLineTaxId();
    QLineEdit *getLineShortName();
    QComboBox *getBoxName();
    Button *getPushNew();
    Button *getPushEdit();
    Button *getPushSave();
    Button *getPushDelete();
    QTableWidget *getTableTaxes();
    QVector<Tax> getTaxes();
    void setTaxes(QVector<Tax> taxes);
  /**
    Konstruktor inicjujący wszystkie elementy dla danego widgeta
    @param
    parent - wskaźnik określający rodzica widgeta, wykorzystywany w programie
    controller - wskaźnik do obiektu zawierającego kontrolki dla atrybutów danej klasy
  */
    explicit SettingsTaxesView(SettingsTaxesController *controller, QWidget *parent = 0);
  /**
    Destruktor dla danej klasy, usuwa smodel
   */
    ~SettingsTaxesView();
  /**
    Metoda która definiuje oraz inicjuje wszystkie komórki w tabeli, określa ich zawartość oraz cechy
   */
    void createItem(QTableWidgetItem *item, int i);

};

#endif // SETTINGSPANELVIEW_H
