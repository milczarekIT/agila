#ifndef SelectOrderController_H
#define SelectOrderController_H

#include "Document/OrderDocument/OrderDocumentTVModel.h"
#include "Document/OrderDocument/OrderService.h"
#include "SelectionWindows/SelectInvoiceView.h"
#include "SelectionWindows/SelectVisibleColumns.h"
#include "Other/ITableStateManager.h"
class SelectInvoiceView;

class SelectOrderController  : public QObject, public ITableStateManager   {
    Q_OBJECT

private:

    QString docTypeFilter;
    int cancel;
    /**
    Okienko dialogowe wyboru kontrahenta
    */
    SelectInvoiceView* view;
    /**
    Wskaźnik do modelu kontrahenta, dzieki niemu ładujemy liste kontrahentów
    do okna wyboru kontrahenta dla danej faktrury.
    */
    OrderDocumentTVModel *orderDocumentTVModel;
    SelectVisibleColumns *selectColumnsDialog;

    void initOrderTable();
    /**
      * Metoda inicjująca, wspólna dla dwóch konstruktorów. C++ nie pozwala na wywołanie innego konstruktora wew. tej samej klasy
      */
    void init(QWidget* parent);

    void restoreTableState();
    void saveTableState();

public:
    /**
    Gettery do powyższych zmiennych.
    */
    int getCancel();
    SelectInvoiceView *getView();
    /**
    Konstruktor inicjujący wskaźnik do okienka dialogowego dla danej klasy
    @param
    parent - przekazywany dalej do klasy SelectContractorView, określa rodzica okna
    */
    SelectOrderController(QWidget* parent,QString docTypeFilter =0);
    /**
    Destruktor danej klasy;
    */
    ~SelectOrderController();
    /**
    Metoda publiczna odpowiedzialna za wywołanie interfejsu graficznego okna
    */
    void showDialog();
    /**
    Metoda publiczna odpowiedzialna za dodanie wybranego kontrahenta do okna faktury,
    zwraca strukture kontrahenta .
    */
    Order addOrder();

public slots:
    /**
    Slot publiczny wywolywany w celu zamknięcia okna bez załadowania kontrahenta
    ustawia zmienna cancel
    */
    void setCancel();
    void dialogSelectColumns();
    void changeColumnVisiblity(QList<int> visibleColumns);
};

#endif // SelectOrderController_H
