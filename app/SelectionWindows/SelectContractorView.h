#ifndef SELECTCONTRACTORVIEW_H
#define SELECTCONTRACTORVIEW_H

#include <QGridLayout>
#include <QDialog>
#include "Components/Button.h"
#include <QTabWidget>
#include <QTableWidget>

#include "Components/TableView.h"
#include "SelectionWindows/SelectContractorController.h"

class SelectContractorController;
/**
 * Gdy klikniemy w "dodaj dostawcę" / "zmień kontrahenta" w oknie tworzenia faktury lub innego dokumentu,
 * ta klasa ma wyświetlić okno umozliwiające wybranie nam kontrahenta
 */
class SelectContractorView : public QDialog {
    Q_OBJECT

private:

    QGridLayout* mainLayout;
    Button* buttonContractorAdd;
    Button* buttonAnuluj;
    Button* buttonContractorAddNew;
    Button* buttonEdit;
    Button* buttonSelectColumns;
    TableView* contractorsTable;
    QWidget *filterWidget;
    SelectContractorController * controller;

    QLineEdit *lineContractorName;
    QLineEdit *lineContractorSymbol;
    QLineEdit *lineContractorNip;

    void initButtons();
    void initTable();
    void initFilterWidget();
    void addAllComponents();
    void initConnections();

public:


    /**
      *Konstruktor ze wskaznikiem do bazy danych(Kontrachentow) ktorej polaczenie nawiazano w MainWindow,
      *przekazany przez FactureVatEditDialog.
      */
    explicit SelectContractorView(QWidget *parent , SelectContractorController * controller);
    ~SelectContractorView();
     TableView *getContractorsTable();
     void closeEvent(QCloseEvent *event);

     QLineEdit *getLineContractorName();
     QLineEdit *getLineContractorSymbol();
     QLineEdit *getLineContractorNip();

};

#endif // SELECTCONTRACTORVIEW_H
