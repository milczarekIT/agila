#ifndef SETTINGSDOCUMENTTEXTVIEW_H
#define SETTINGSDOCUMENTTEXTVIEW_H

#include <QLabel>
#include <QWidget>
#include <QVector>
#include <QLineEdit>
#include <QGridLayout>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "Database/Database.h"
#include "Settings/SettingsModel.h"
#include "Settings/SettingsAbstractItemView.h"
#include "SettingsDocumentTextController.h"
class SettingsDocumentTextController;

class SettingsDocumentTextView : public SettingsAbstractItemView
{
    Q_OBJECT
private:
      SettingsDocumentTextController *controller;
    /**
      TableWidget który zawiera typy dokumentów oraz tekst który się pod nimi wyświetla, ładowany jest do niego
      vektor pobrany z bazy danych
    */
      QTableWidget * tableDTextes;
      QVector<DocumentInfo> documentsInfo;
    /**
      Zmienna logiczna sprawdzajaca czy tekst w komorce jest zmieniony przez nas czy przez program, ktory laduje stara wartosc do owej
      komorki w przypadku niezaakceptowania zmian wprowadzonych przez uzytkownika
     */
      bool isEdited;
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
    explicit SettingsDocumentTextView(SettingsDocumentTextController *controller,QWidget *parent = 0);
    /**
      Metoda publiczna tworząca komórki dla danej tabeli, wraz z ich odpowiednia zawartoscia, dla podanego wiersza
      */
    void createItem(int i);
    /**
      @see createItem(int i);
      Tworzy elementy tabeli, ladujac do niej dane z bazy danych
      */
    void updateTable();
    /**
      Gettery dla atrybutow/widgetow danej klasy - analogicznie do ich nazwy
     */
    void setTableSettings();
    QTableWidget *getTableDTextes();
    QVector<DocumentInfo> getDocumentsInfo();
    void setDocumentsInfo(QVector<DocumentInfo> documentsInfo);
    void setIsEdited(bool isEdited);
    bool getIsEdited();

  /**
    Destruktor dla danej klasy, usuwa smodel
   */
    ~SettingsDocumentTextView();
};

#endif // SETTINGSDOCUMENTTEXTVIEW_H
