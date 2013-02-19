#ifndef WAREHOUSEDIALOGVIEW_H
#define WAREHOUSEDIALOGVIEW_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QRadioButton>
#include "Components/ButtonBox.h"
#include "Other/Warehouse/Warehouse.h"
#include "Settings/StoreSettings/WarehouseDialogController.h"
class WarehouseDialogController;

class WarehouseDialogView : public QDialog
{
    Q_OBJECT
private:
    WarehouseDialogController *controller;
    QGridLayout *layout;
    QLineEdit *lineName;
    QLineEdit *lineShortName;
    ButtonBox *buttonBox;
    QCheckBox *checkBoxDefault;
    QButtonGroup *buttonGroup;
    QGroupBox *groupBox;
    QLabel *lineNameNotAvailable;
    QLabel *lineShortNameNotAvailable;

    void initComponents();
    void initConnections();
public:
    WarehouseDialogView(WarehouseDialogController *controller, QWidget *parent);

    QLineEdit *getLineName();
    QLineEdit *getLineShortName();
    QCheckBox *getCheckBoxDefault();
    QGroupBox *getGroupBox();
    QButtonGroup* getButtonsImportWarehouse();
    QLabel *getLineNameNotAvailable();
    QLabel *getLineShortNameNotAvailable();
};

#endif // WAREHOUSEDIALOGVIEW_H
