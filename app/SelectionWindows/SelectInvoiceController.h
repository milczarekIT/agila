#ifndef SELECTINVOICECONTROLLER_H
#define SELECTINVOICECONTROLLER_H

#include "Document/SaleDocument/SaleDocumentTVModel.h"
#include "Document/SaleDocument/InvoiceService.h"
#include "Document/SaleDocument/DocumentZALService.h"
#include "Document/PurchaseDocument/PurchaseInvoiceService.h"
#include "SelectionWindows/SelectInvoiceView.h"
#include "SelectionWindows/SelectVisibleColumns.h"
#include "Document/PurchaseDocument/PurchaseDocumentTVModel.h"
#include "Other/ITableStateManager.h"
class SelectInvoiceView;

class SelectInvoiceController  : public QObject, public ITableStateManager  {
    Q_OBJECT

private:

    int cancel;

    SelectInvoiceView* view;
    DocumentTVModel *documentTVModel;
    SelectVisibleColumns *selectColumnsDialog;

    /**
      * Lista z z typami dokumentów do wyświetlenia w oknie
      * np. docTypeFilter << "FV" << "FMP";
      */
    QStringList docTypeFilter;

    void initInvoiceTable();
    /**
      * Metoda inicjująca, wspólna dla dwóch konstruktorów.
      */
    void init(QWidget* parent, QString documentFamily);

    void restoreTableState();
    void saveTableState();

public:
    /**
    Gettery do powyższych zmiennych.
    */
    int getCancel();
    SelectInvoiceView *getView();

    SelectInvoiceController(QWidget* parent);
    /**
    Konstruktor inicjujący wskaźnik do okienka dialogowego dla danej klasy
    @param docTypeFilter - QStringLista z typami dokumentów (sprzedaży do wsyświetlenia w oknie
    @see SelectInvoiceController(QWidget* parent);
    @example    QStringList docTypeFilter;
                docTypeFilter << "FV" << "FMP" << "PRO";
                SelectInvoiceController dialog(docTypeFilter,view);
    */
    SelectInvoiceController(QWidget* parent, QStringList docTypeFilter);

    /** documentFamily np. SALE, PURCHASE **/
    SelectInvoiceController(QWidget* parent, QString documentFamily);

    ~SelectInvoiceController();

    void showDialog();
    /**
    Metoda publiczna odpowiedzialna za dodanie wybranego kontrahenta do okna faktury,
    zwraca strukture kontrahenta .
    */
    Document addInvoice();

    /** Wyklucza typ documentu podany w parametrze **/
    void setDocumentNotTypeFilter(QString excludedType);

public slots:
    /**
    Slot publiczny wywolywany w celu zamknięcia okna bez załadowania kontrahenta
    ustawia zmienna cancel
    */
    void setCancel();
    void dialogSelectColumns();
    void changeColumnVisiblity(QList<int> visibleColumns);

    void setDocumentSymbolFilter(QString text);
};

#endif // SELECTINVOICECONTROLLER_H
