#ifndef SELECTINVOICEVIEW_H
#define SELECTINVOICEVIEW_H

#include <QGridLayout>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include "Components/TableView.h"
#include "Components/Button.h"
#include "SelectionWindows/SelectInvoiceController.h"
#include "SelectionWindows/SelectOrderController.h"
class SelectInvoiceController;
class SelectOrderController;
class SelectInvoiceView : public QDialog {
    Q_OBJECT

private:
    QGridLayout* mainLayout;
    Button* buttonInvoiceSelect;
    Button* buttonCancel;
    Button* buttonSelectColumns;
    TableView* invoiceTable;
    QWidget* filterWidget;
    QLineEdit *lineSymbolFilter;
    SelectInvoiceController *controllerInvoice;
    SelectOrderController *controllerOrder;
    void init();
    void initButtons();
    void initTable();
    void initFilterWidget();
    void addAllComponents();
    void initConnections();
    void initInvoiceConnections();
    void initOrderConnections();


public:
    /**
      *Konstruktor ze wskaznikiem do bazy danych(Kontrachentow) ktorej polaczenie nawiazano w MainWindow,
      *przekazany przez FactureVatEditDialog.
      */
    explicit SelectInvoiceView(QWidget *parent , SelectInvoiceController * controller);
    explicit SelectInvoiceView(QWidget *parent, SelectOrderController * controller);
    ~SelectInvoiceView();
    void closeEvent(QCloseEvent *event);
    TableView* getInvoiceTable();

};

#endif // SELECTINVOICEVIEW_H
