#ifndef MAINTABCONTRACTORSITEMCONTROLLER_H
#define MAINTABCONTRACTORSITEMCONTROLLER_H

#include <QWidget>
#include "Main/MainTabItemController.h"
#include "Main/MainTabContractorsItem.h"
#include "Contractor/ContractorTVModel.h"
#include "Contractor/ContractorGroupModel.h"
#include "Contractor/ContractorDialogController.h"
#include "Other/TableStateManager.h"
#include "Other/ITableStateManager.h"
#include "SelectionWindows/SelectVisibleColumns.h"
class MainTabContractorsItem;

class MainTabContractorsItemController : public MainTabItemController, public ITableStateManager
{
    Q_OBJECT

private:
    MainTabContractorsItem *view;
    ContractorTVModel *contractorTVModel;
    ContractorService *contractorService;
    TableStateManager *tableStateManager;
    SelectVisibleColumns *selectColumnsDialog;

    void restoreTableState();
    void saveTableState();
    void initSelectingColumnVisibility();

public:

    MainTabContractorsItemController();
    ~MainTabContractorsItemController();
    MainTabItem *getView();
    void initComboBox();
    void fillBox(QComboBox *box,QVector<ContractorGroup> values);
    void initModel();
    void refreshTable();
    ModuleManager::Module module();

public slots:
    void dialogContractorAdd();
    void dialogContractorEdit();
    void removeContractor();
    void setConNameFilter(QString filter);
    void setConNipFilter(QString filter);
    void setConSymbolFilter(QString filter);
    void setConGroupFilter(int index);
    void setConTypeFilter(int index);
    void dialogSelectColumns();
    void changeColumnVisiblity(QList<int> visibleColumns);

signals:
    void settingsChangedSignal(const QString element);

public slots:
    void settingsChanged(const QString element);
};

#endif // MAINTABCONTRACTORSITEMCONTROLLER_H
