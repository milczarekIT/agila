#ifndef SETTINGSDOCUMENTNUMBERINGVIEW_H
#define SETTINGSDOCUMENTNUMBERINGVIEW_H

#include <QLabel>
#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include "Components/Button.h"
#include "Database/Database.h"
#include "Settings/SettingsAbstractItemView.h"
#include "SettingsDocumentNumberingController.h"

class SettingsDocumentNumberingController;

/**
  @author Janiu
  Klasa widgeta zawierającego elementy ustawień numerowania dokumentow
  */
class SettingsDocumentNumberingView : public SettingsAbstractItemView
{
    Q_OBJECT
private:
  /**
    Wskaźnik do klasy zawierającej wszystkie kontrolki dla elementów badanego widgeta
  */
    SettingsDocumentNumberingController *controller;
  /**
    LineEdit służacy do definiowania lub przechowujący znak specjalny dla numerowania
  */
    QLineEdit *sign;
  /**
    ComboBox który pobiera z bazy danych model zawierajacy dane o wszystkich sposobach numerowania
  */
    QComboBox *kindsOfNumbering;
    QComboBox *whichModule;
  /**
    QLabel ktory zawiera nazwe dokumentu dla aktualnie przegldanej numeracji
  */
    QLineEdit *numberingDocument;
  /**
    LineEdit przechwujący zawartosc sposobu numerowania bez nazwy dokumentu
  */
    QLineEdit *numberingRest;
  /**
    Button ktory definiuje dla numerowania rok
  */
    Button *year;
  /**
    Button ktory definiuje dla numerowania miesiace
  */
    Button *month;
  /**
    Button ktory definiuje dla numerowania dni
  */
    Button *day;
  /**
    Button ktory definiuje dla numerowania numery
  */
    Button *numbering;
    Button *pushSave;


public:
   /**
    Konstruktor inicjujący wszystkie elementy dla danego widgeta
    @param
    parent - wskaźnik określający rodzica widgeta, wykorzystywany w programie
    controller - wskaźnik do obiektu zawierającego kontrolki dla atrybutów danej klasy
  */
    explicit SettingsDocumentNumberingView(SettingsDocumentNumberingController *controller, QWidget *parent = 0);
   /**
    Metoda ktora definiuje wyglad buttonow bedacych edytorami dla numerowania dokumentow
     */
    void createEditorButton(QPushButton *button);
   /**
     Gettery i settery dla atrybutów danej klasy - nazwy analogiczne do nazw atrybutów
    */
    QLineEdit *getSign();
    QComboBox *getKindsOfNumbering();
    QComboBox *getWhichModule();
    QLineEdit *getNumberingDocument();
    QLineEdit *getNumberingRest();
    Button *getYear();
    Button *getMonth();
    Button *getDay();
    Button *getNumbering();
    Button *getPushSave();
    void setWarehouse(QString name);
    void initGraphicElements();
    void setGraphicSettings();
    void setInterfaceController();
  /**
    Metoda, która tworzy nam interfejs przycisków odpowiedzialnych za definiowanie rodzajow numerowania
    */
    QFrame *createTablesInterface();

};

#endif // SETTINGSDOCUMENTNUMBERINGVIEW_H
