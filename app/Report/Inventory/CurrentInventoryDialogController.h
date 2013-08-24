#ifndef CURRENTINVENTORYDIALOGCONTROLLER_H
#define CURRENTINVENTORYDIALOGCONTROLLER_H

#include <QWidget>
#include <Qt>
#include <QVariant>
#include "Report/Inventory/CurrentInventoryDialogView.h"
#include "Report/Inventory/CurrentInventoryTVModel.h"
#include "Report/ReportDialogController.h"



class CurrentInventoryDialogView;

class CurrentInventoryDialogController  : public ReportDialogController
{
    Q_OBJECT
private:
    CurrentInventoryDialogView *view;
    CurrentInventoryTVModel *tvModel;

    void restoreTableState();
    void saveTableState();

public:
    explicit CurrentInventoryDialogController(QWidget *parent);
    ~CurrentInventoryDialogController();

    void exec();

public slots:
    void showWithZeroQuantity(bool checked);
    void saveReport();
};

#endif // CURRENTINVENTORYDIALOGCONTROLLER_H
