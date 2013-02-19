#ifndef SETTINGSDOCUMENTTEXTCONTROLLER_H
#define SETTINGSDOCUMENTTEXTCONTROLLER_H

#include <QWidget>
#include "Database/Database.h"
#include "Components/MessageBox.h"
#include "SettingsDocumentTextView.h"
#include "Settings/SettingsAbstractItemController.h"
class SettingsDocumentTextView;
class DocumentInfoModel;
/**
  @author Janiu
  Klasa odpowiedzialna za nadanie kontrolek zakładce ustawień tekstu pod dokumentem dla tabWidgetSettings.
  */

class SettingsDocumentTextController : public SettingsAbstractItemController
{
    Q_OBJECT
private:
  /**
  QWidget z gama elementów służącą do ustawień tekstów pod dokumentami, wykorzystywany do nadania mu odpowiedniej funkcjonalności
  */
    SettingsDocumentTextView *view;
    DocumentInfoModel *documentInfoModel;
    bool dialogLoop;

public:
  /**
   Konstruktor inicjujący wskaźnik do widgeta dla danej klasy
  @param
    parent - przekazywany dalej do klasy SettingsDocumentTextesView, określa rodzica okna
  */
    explicit SettingsDocumentTextController(QWidget *parent = 0);
    ~SettingsDocumentTextController();
   /**
    Metoda publiczna zwracająca wskaźnik do interfejsu graficznego aktualnego widgeta
   */
    SettingsDocumentTextView *getView();
   /**
    Metoda publiczna która poddaje edycji tekst dla danego dokumentu, na podstawie wprowadzonych wartosci oraz akceptacji operacji
   */
    void editText();
    DocumentInfoModel *getModel();
    void updateTable();
    void updateTableByModules();
    void setModel();

public slots:
   /**
     @see editText()
     Slot publiczny, który po zakonczeniu edycji danej komorki wyswietla zapytanie o potwierdzenie lub odrzucenie operacji
     oraz w razie potwoerdzenia edytujacy tekst w bazie dla danego dokumentu
     */
    void acceptAction();
};

#endif // SETTINGSDOCUMENTTEXTCONTROLLER_H
