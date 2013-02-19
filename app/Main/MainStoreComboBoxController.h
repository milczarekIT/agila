#ifndef MAINSTORECOMBOBOXCONTROLLER_H
#define MAINSTORECOMBOBOXCONTROLLER_H

#include <QWidget>
#include "Main/MainStoreComboBox.h"
#include "Other/Warehouse/WarehouseModel.h"
#include "Other/Application/ApplicationManager.h"
class MainStoreComboBox;

class MainStoreComboBoxController : public QWidget
{
    Q_OBJECT

private:
    MainStoreComboBox *view;
    WarehouseService *warehouseService;

public:
    explicit MainStoreComboBoxController();
    ~MainStoreComboBoxController();
    MainStoreComboBox *getView();

public slots:
    void switchStore(int index);
    void setDataIntoStoreComboBox();
    void setCurrentStoreInStoreComboBox();

signals:
    void storeSwitched();

};

#endif // MAINSTORECOMBOBOXCONTROLLER_H
