#ifndef SETTINGSDOCUMENTNUMBERINGCONTROLLER_H
#define SETTINGSDOCUMENTNUMBERINGCONTROLLER_H

#include <QWidget>
#include "Components/MessageBox.h"
#include "Document/DocumentInfoModel.h"
#include "SettingsDocumentNumberingView.h"
#include "Settings/SettingsAbstractItemController.h"
class SettingsDocumentNumberingView;

/**
  @author Janiu
  Klasa odpowiedzialna za nadanie kontrolek zakładce ustawień numerowania dokumentów dla tabWidgetSettings.
  */
class SettingsDocumentNumberingController : public SettingsAbstractItemController
{
    Q_OBJECT
private:
   SettingsDocumentNumberingView *view;
  /**
    Wartość przechowująca aktualną formę przeglądanej numeracji przed zmianami, bez nazwy dokumentu
    */
    QString whichSymbols;
    QString numberingState;
    DocumentInfoModel *documentInfoModel;
    void fillBox(QComboBox *box,QVector<DocumentInfo> values);

public:
  /**
   Konstruktor inicjujący wskaźnik do widgeta dla danej klasy
  @see
    setModelToComboBox();
    showDocumentNumbering();
  @param
    parent - przekazywany dalej do klasy SettingsDocumentNumberingView, określa rodzica okna
   */
    explicit SettingsDocumentNumberingController(QWidget *parent = 0);
    ~SettingsDocumentNumberingController();

    SettingsDocumentNumberingView *getView();
  /**
   Metoda publiczna dopisująca do lineEdit'a numberingRest podaną w parametrze wartość poprzedzoną "/"
   */
    void insertElementToNumbering(QString value);
  /**
   Metoda publiczna wyszukująca w numberingRest wartość aktualnego znaku specjalnego
   */
    QString findSignText();
  /**
   Metoda publiczna ktora z numberingRest usuwa podany string, wpierw poprzedzony "/", jesli owego nie ma
   to zakonczony "/", ostatecznie sam string bez dodatkow
   */
    void deleteElementFromNumbering(QString value);
  /**
   @see
    findSignText()
   Metoda publiczna, która zaznacza buttony ktorych tresc zawiera się w aktualnie przegladanym numerowaniu dokumentow
  */
    void matchUsedForm(QString str);
  /**
   @see
    editDocumentNumbering();
   Metoda publiczna sprawdzajaca podczas zmiany indexu comboboxa czy w numerowaniu nie zostaly czasem dokonane zmiany
  */
    bool containsString(QString value);
    void setModel();
    DocumentInfoModel *getModel();

public slots:
    void checkIfChanged();
  /**
   @see
    deleteElementFromNumbering();
    createInfoBox();
    findSignText();
    showDocumentNumbering();
    insertElementToNumbering();

   Slot publiczny reagujący na zakonczenie edycji wartosci w polu sign, gdy w tym polu znajduje sie wartosc "Znak specjalny"
   nie robi nic, gdy pole jest puste wpisuje w nie "Znak specjalny", w kazdym innym przypadku zawartosc sign laduje do numberingRest
   chyba ze stanowi ona lub zawiera wartosci zakazane
  */
    void releaseLineNumbering();
  /**
   Slot publiczny, ktory przy dwukrotnym kliknieciu czysci lineEdit Sign, ktory zawiera wartosc "Znak specjalny"
  */
    void clickedLineNumbering();

  /**
   @see
    insertElementToNumbering()
    deleteElementFromNumbering()
   Slot publiczny, ktory przy kliknieciu na button year ustawia go na checked albo unchecked oraz odpowiednio dodaje wartosc
   /YYYY do numberingRest badz tez ja usuwa
  */
    void actionYear();
  /**
   @see
    insertElementToNumbering()
    deleteElementFromNumbering()
   Slot publiczny, ktory przy kliknieciu na button day ustawia go na checked albo unchecked oraz odpowiednio dodaje wartosc
   /DD do numberingRest badz tez ja usuwa
  */
    void actionDay();
  /**
   @see
    insertElementToNumbering()
    deleteElementFromNumbering()
   Slot publiczny, ktory przy kliknieciu na button month ustawia go na checked albo unchecked oraz odpowiednio dodaje wartosc
   /MM do numberingRest badz tez ja usuwa
  */
    void actionMonth();
  /**
   @see
    insertElementToNumbering()
    deleteElementFromNumbering()
   Slot publiczny, ktory przy kliknieciu na button numbering ustawia go na checked albo unchecked oraz odpowiednio dodaje wartosc
   /# do numberingRest badz tez ja usuwa
  */
    void actionNumbering();
  /**
   @see
    matchUsedForm();
    checkIfChanged();
   Slot publiczny wyswitlający informacje w odpowiednich widgetach o aktualnie wybranym z combo boxa sposobie numerowania
   dokumentow, sprawdza
  */
    void showDocumentNumbering();
  /**
   @see
    setModelToComboBox();
   Slot publiczny ktory dokonuje edycji dla aktualnie przegladanego sposobu numerowania dokumentow w bazie danych
  */
    void editDocumentNumbering();
    void setWhichSymbols();

};

#endif // SETTINGSDOCUMENTNUMBERINGCONTROLLER_H
