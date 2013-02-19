#ifndef GOODSDIALOGVIEW_H
#define GOODSDIALOGVIEW_H

#include <QGridLayout>
#include <QLineEdit>
#include <QDialog>
#include <QLabel>
#include <QDialogButtonBox>
#include <QTabWidget>
#include <QComboBox>
#include <QTableView>
#include <QGraphicsView>
#include <QTextEdit>
#include <QGroupBox>
#include <QMouseEvent>
#include <QRadioButton>
#include <QTableWidget>
#include <QMenu>
#include "Components/ButtonBox.h"
#include "Components/Button.h"
#include "Database/Database.h"
#include "Goods/Goods.h"
#include "Goods/GoodsModel.h"
#include "Settings/SettingsModel.h"
#include "Goods/GoodsDialogController.h"
class GoodsDialogController;
class GoodsValidator;

/**
  @author Janiu
  Klasa okienka dialogowego dodawania/edycji dóbr
  */
class GoodsDialogView : public QDialog
{
    Q_OBJECT

public:
    explicit GoodsDialogView(QWidget *parent, GoodsDialogController *controller);
    ~GoodsDialogView();

    QLineEdit *getLineSymbol();
    QLineEdit *getLineName();
    QLineEdit *getLineTax();
    QLineEdit *getLinePkwiu();
    QLineEdit *getLinePriceMagNet();
    QLineEdit *getLinePriceMagGross();
    QLineEdit *getLineWeight();
    QRadioButton *getRadioGood();
    QRadioButton *getRadioService();
    QTextEdit *getTextDescription();
    QComboBox *getBoxGoodGroup();
    QComboBox *getBoxUnit();
    QComboBox *getBoxTax();
    QLabel *getPicture();
    QTableView *getTableFeatures ();
    QTabWidget *getTabWidget();
    QComboBox *getAddToWarehouseComboBox();
    QTableWidget *getTablePrices();
    void addWarehouseSelection();


private:

    QTableWidget * tablePrices;
    QLineEdit *lineSymbol;
    QLineEdit *lineName;
    QLineEdit *lineTax;
    QLineEdit *linePkwiu;
    QLineEdit *linePriceMagNet;
    QLineEdit *linePriceMagGross;
    QLineEdit *lineWeight;
    QRadioButton *radioGood;
    QRadioButton *radioService;
    QTextEdit *textDescription;
    QFrame * framePicture;

    QMenu *context;

    QTableView *tableFeature;
/**
  Walidator cen
  */
    QRegExpValidator *priceValidator;

    QComboBox *boxGoodGroup;
    QComboBox *boxUnit;
    QComboBox *boxTax;
 /**
    Element przechowujący i wyświetlający zdjęcie danego towaru
 */
    QLabel *picture;

    QGridLayout *standardLayout;
    QGridLayout *pricesLayout;
    QGridLayout *featuresLayout;
  /**
    Główny tabWidget, zawierający zakładki Podstawowe i Ceny, umieszczone są w nim wszystkie elementy okna
  */
    QTabWidget *tabWidget;

    QWidget *tabStandard;
    QWidget *tabPrices;
    QWidget *tabFeatures;

    ButtonBox *buttonBox;

    QPushButton *pushAddGroup;
    QPushButton *pushDeleteGroup;
    QPushButton *pushAddFeature;
    QPushButton *pushDeleteFeature;
    Button *pushAddTax;
    Button *pushDeleteTax;

    QComboBox *addToWarehouseComboBox;

    GoodsDialogController *controller;

  /**
    Metoda służąca do ustawienia elemetów manipulacji danymi wraz z odpowiednimi dla nich labelami w naszych layoutach
    standard i prices

    @param
     layout - layout w jakim mają zostać umieszczone podane elementy
     widget - element w ktorym umieszczamy dane, badz z którego te dane wybieramy
     label - informacja o funkcji danego elementu zawierającego dane
     labelValue - string umieszczany w labelu
     col1,col2,col3,col4 - wspólrzędne danych obiektów w layoucie
  */
    void setComponents(QGridLayout *layout,QWidget *widget, QString lineEditValue, int col1,int col2, int col3, int col4);
    void setComponents(QGridLayout *layout,QWidget *widget, int col1,int col2, int col3, int col4);
  /**
    @see setComponents()
    Metoda inicjująca wszystkie elementy należace do zakładki Podstawowe naszego głównego tabWidgeta
  */
    void addAllStandardComponents();
  /**
    @see setComponents()
    Metoda inicjująca wszystkie elementy należace do zakładki Ceny naszego głównego tabWidgeta
  */
    void addAllPriceComponents();
    void createTablePrices();
  /**
    jw tylko że dla cech
  */
    void addAllFeatureComponents();
  /**
    Metoda inicjująca manipulacyjne elementy okna, typu buttonBox odpowiedzialny za akceptacje badź przerwanie operacji w oknie
    oraz zamknięcie okna
  */
    void createMenu();
  /**
    Metoda inicjująca cechy głównego tabWidgeta z którego korzystamy, m.in. zakładki, rozmiary, layouty
  */
    void createTabWidget();
    void setTabOrders();
protected:
    void mouseReleaseEvent(QMouseEvent *pEvent);
    void closeEvent(QCloseEvent *event);

signals:
    void settingsChangedSignal(const QString element);

public slots:
    void settingsChanged(const QString element);

};

#endif
