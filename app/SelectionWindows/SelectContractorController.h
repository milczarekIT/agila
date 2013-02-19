#ifndef SELECTCONTRACTORCONTROLLER_H
#define SELECTCONTRACTORCONTROLLER_H

#include "Database/Database.h"
#include "SelectionWindows/SelectContractorView.h"
#include "SelectionWindows/SelectVisibleColumns.h"
#include "Contractor/ContractorService.h"
#include "Contractor/ContractorDialogView.h"
#include "Contractor/ContractorTVModel.h"
#include "Other/TableStateManager.h"
#include "Other/ITableStateManager.h"
class SelectContractorView;

class SelectContractorController : public QObject, public ITableStateManager  {
    Q_OBJECT

private:

    int cancel;
    SelectContractorView* view;
    ContractorService *conService;
    ContractorTVModel *contractorTVModel;

    TableStateManager *tableStateManager;
    SelectVisibleColumns *selectColumnsDialog;

    /**
    Odpowiada za załadowanie modelu kontrahentów w tablicy
    */
    void initContractorsTable();
    /**
    Odpowiada za edycje kontraktora z poziomu okna wyboru towaru dla faktury
    */
    void editContractor(int id=0);

    void restoreTableState();
    void saveTableState();
    void initFilterTable();

public:
    /**
    Gettery do powyższych zmiennych.
    */
    int getCancel();
    SelectContractorView *getView();
    /**
    Konstruktor inicjujący wskaźnik do okienka dialogowego dla danej klasy
    @param
    parent - przekazywany dalej do klasy SelectContractorView, określa rodzica okna
    */
    SelectContractorController(QWidget* parent);
    ~SelectContractorController();
    /**
    Metoda publiczna odpowiedzialna za wywołanie interfejsu graficznego okna
    */
    void showDialog();
    /**
    Metoda publiczna odpowiedzialna za dodanie wybranego kontrahenta do okna faktury,
    zwraca strukture kontrahenta .
    */
    Contractor addContractor();

    /** Filtr dla typów Kontrahenta, pozwala wybrać np. tylko dostawców lub odbiorców **/
    void setContractorTypeFilter(int contractorType);

public slots:
    void addNewContractor();
    /**
    Slot publiczny wywolywany w celu zamknięcia okna bez załadowania kontrahenta
    ustawia zmienna cancel
    */
    void setCancel();
    void dialogContractorEdit();
    void dialogSelectColumns();
    void changeColumnVisiblity(QList<int> visibleColumns);

    void setContractorNameFilter(QString text);
    void setContractorSymbolFilter(QString text);
    void setContractorNipFilter(QString text);

};

#endif // SELECTCONTRACTORCONTROLLER_H
