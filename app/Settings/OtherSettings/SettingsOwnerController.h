#ifndef SETTINGSOWNERCONTROLLER_H
#define SETTINGSOWNERCONTROLLER_H

#include <QDir>
#include <QFile>
#include <QWidget>
#include <QTextStream>
#include <QFileDialog>
#include <QDomDocument>
#include <QXmlStreamWriter>
#include "Other/Owner/Owner.h"
#include "Other/Owner/OwnerService.h"
#include "Components/MessageBox.h"
#include "SettingsOwnerView.h"
#include "Settings/SettingsAbstractItemController.h"
#include "Other/OtherService.h"
class SettingsOwnerView;

/**
  @author Janiu
  Klasa odpowiedzialna za nadanie kontrolek zakładce ustawień podmiotu dla tabWidgetSettings.
 */
class SettingsOwnerController : public SettingsAbstractItemController
{
    Q_OBJECT
private:
   /**
     Element zapisywanej informacji
   */
    QDomElement root;
    OwnerService *ownerService ;
   /**
    QWidget z gama elementów służącą do ustawień odmiotu, wykorzystywany do nadania mu odpowiedniej funkcjonalności
   */
    SettingsOwnerView *view;

    int accountNumberLength;

    Owner o;

public:
  /**
    Konstruktor inicjujący wskaźnik do widgeta dla danej klasy
    @param
     parent - przekazywany dalej do klasy SettingsOwnerView, określa rodzica okna
  */
    explicit SettingsOwnerController(QWidget *parent);
    explicit SettingsOwnerController(); // gdy tylko pobranie danych o podmiocie
  /**
   Metoda publiczna udostępniająca załadowanie danych z elementów interfejsu do obiektu klasy Owner
   */
    void setOwnerData();
  /**
   Metoda publiczna udostępniająca pobranie z pliku XML danych i załadowanie ich do obiektu klasy Owner
   */
    void getOwnerData();
  /**
   Metoda publiczna udostępniająca załadowanie danych z obiektu klasy Owner do elementów interfejsu
   ustawien dla podmiotu
   */
    void insertOwnerData1();
  /**
   Metoda publiczna zwracająca wskaźnik do interfejsu graficznego aktualnego widgeta
   */
    SettingsOwnerView *getView();
    void setModel();

 public slots:
  /**
   @see
    receiveData()
   Slot publiczny zapisujący otrzymane dane do pliku xml
   */
    int saveData();

    void setLogo();
    void removeLogo();

    void autoPostalCode();

};

#endif // SETTINGSOWNERCONTROLLER_H
