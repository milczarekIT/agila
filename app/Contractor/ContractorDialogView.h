#ifndef CONTRACTORSEDITVIEW_H
#define CONTRACTORSEDITVIEW_H

#include <QVBoxLayout>
#include <QLineEdit>
#include <QDialog>
#include <QLabel>
#include "Components/Button.h"
#include <QTabWidget>
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QComboBox>
#include <QRadioButton>
#include <QTextEdit>
#include <QCloseEvent>
#include <QTableView>
#include "Components/ButtonBox.h"
#include "Contractor/ContractorModel.h"
#include "Contractor/ContractorDialogController.h"
class ContractorDialogController;
class ContractorValidator;

/**
  @author Janiu
  Klasa okienka dialogowego dodawania/edycji kontrahentów
  */
class ContractorDialogView : public QDialog
{
    Q_OBJECT

public:
/**
    Konstruktor inicjujący wskaźnik do okienka dialogowego dla danej klasy
    @param
    parent - wskaźnik określający rodzica okna, wykorzystywany w programie
    controller - wskaźnik do obiektu zawierającego kontrolki dla atrybutów danej klasy
*/
    explicit ContractorDialogView(QWidget *parent,ContractorDialogController *controller);
/**
    Destruktor danej klasy
*/
    ~ContractorDialogView();
 /**
    Gettery dla atrybutów danej klasy, nazwy metod analogiczne do nazw atrybutów
*/
    QLineEdit *getLineSymbol();
    QLineEdit *getTextCompany();
    QLineEdit *getLineName();
    QLineEdit *getLinePostCode();
    QLineEdit *getLineCity();
    QLineEdit *getLineAdress();
    QLineEdit *getLineTIN();
    QLineEdit *getLineRegon();
    QLineEdit *getLineAccount();
    QLineEdit *getLineWebsite();
    QLineEdit *getLineEmail();
    QLineEdit *getLineDiscount();
    QLineEdit *getLineAdditional();
    QTableView *getTablePhones();
    QTextEdit *getTextComments();
    QComboBox *getBoxConGroup();
    QComboBox *getBoxSOM();
    QComboBox *getBoxAdditionalId();
    QRadioButton *getRadioBusiness();
    QRadioButton *getRadioIndividial();
    QLabel *getLabelName();
    QLabel *getLabelCompany();
    QLabel *getLabelTIN();
    ButtonBox *getButtonBox();
    QCheckBox *getCheckBoxSupplier();
    QCheckBox *getCheckBoxBuyer();

    void closeEvent(QCloseEvent *event);

private:
 /**
    Pola, w których umieszczamy najważniejsze dane o kontrahencie, wykorzystywane do umieszczenia tych danych
    w bazie danych, bądź modyfikacji istniejącch informacji o kontrahencie
*/
    QLineEdit *lineSymbol;
    QLineEdit *textCompany;
    QLineEdit *lineName;
    QLineEdit *linePostCode;
    QLineEdit *lineCity;
    QLineEdit *lineAdress;
    QLineEdit *lineTIN;
    QLineEdit *lineRegon;
    QLineEdit *lineAccount;
    QLineEdit *lineWebsite;
    QLineEdit *lineEmail;
    QLineEdit *lineDiscount;
    QLineEdit *lineAdditional;
    QTableView *phones;
    QTextEdit *textComments;
    QRadioButton *radioBusiness;
    QRadioButton *radioIndividual;
    QCheckBox *checkBoxSupplier;
    QCheckBox *checkBoxBuyer;
    QLabel *labelName;
    QLabel *labelCompany;
    QLabel *labelTIN;
    QComboBox * boxAdditionalId;

    QComboBox *boxConGroup;
    QComboBox *boxSOM;

    QGridLayout *standardLayout;
    QGridLayout *additionalLayout;
  /**
    Główny tabWidget, zawierający zakładki Podstawowe i Dodatkowe, umieszczone są w nim wszystkie elementy okna
  */
    QTabWidget *tabWidget;
    QWidget *tabStandard;
    QWidget *tabAdditional;
  /**
    ButtonBox zawierające przyciski potwierdzenia bądź zaprzestania dokonywanej operacji
  */
    ButtonBox *buttonBox;
  /**
    Linia tworząca podziałkę pomiędzy grupami elementów w zakładce Podstawowe
  */
    QFrame *line;
  /**
    Przycisk inicjujący okienko dodawania/edycji grup kontrahentów
   */
    Button *buttonAddGroup;
  /**
    Przycisk usuwający grupę kontrahentów aktualnie wskazywaną przez boxConGroup
  */
    Button *buttonRemoveGroup;
    /**
      * Przyciski dodawania i usuwania źródła pozyskania klienta (SourceOfMember)
      */
    Button *buttonAddSOM;
    Button *buttonRemoveSOM;
    /**
      Przycisk dodawania nowego telefonu
      */
    Button *buttonAddPhone;
    /**
      Przycisk usuwajacy telefon
      */
    Button *buttonRemovePhone;
  /**
    Wskaźnik do klasy zawierającej wszystkie kontrolki dla elementów badanego okna dialogowego
  */
    ContractorDialogController *controller;

  /**
    Metoda służąca do ustawienia elemetów manipulacji danymi wraz z odpowiednimi dla nich labelami w naszych layoutach
    standard i additional

    @param
     layout - layout w jakim mają zostać umieszczone podane elementy
     widget - element w ktorym umieszczamy dane, badz z którego te dane wybieramy
     label - informacja o funkcji danego elementu zawierającego dane
     labelValue - string umieszczany w labelu
     col1,col2,col3,col4 - wspólrzędne danych obiektów w layoucie
  */
    void setComponents(QGridLayout *layout, QWidget *widget, QString labelValue, int col1,int col2, int col3, int col4);

    /**
      * Podobnie jak wyżej. Zamiast QString labelValue przyjmuje QLabela
      * @see setComponents()
      */
    void setComponents(QGridLayout *layout, QWidget *widget, QLabel *label, int col1,int col2, int col3, int col4);
  /**
    @see setComponents()
    Metoda inicjująca wszystkie elementy należace do zakładki Dodatkowe naszego głównego tabWidgeta
  */
    void addAllAdditionalComponents();
  /**
    @see setComponents()
    Metoda inicjująca wszystkie elementy należace do zakładki Podstawowe naszego głównego tabWidgeta
  */
    void addAllStandardComponents();
  /**
    Metoda inicjująca cechy głównego tabWidgeta z którego korzystamy, m.in. zakładki, rozmiary, layouty
  */
    void createTabWidget();
  /**
    Metoda inicjująca manipulacyjne elementy okna, typu buttonBox odpowiedzialny za akceptacje badź przerwanie operacji w oknie
    oraz zamknięcie okna
  */
    void createMenu();

signals:
    void settingsChangedSignal(const QString element);

public slots:
    void settingsChanged(const QString element);

};

#endif
