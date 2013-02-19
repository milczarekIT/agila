#ifndef CURRENTINVENTORYGROUPSDIALOGCONTROLLER_H
#define CURRENTINVENTORYGROUPSDIALOGCONTROLLER_H

#include <QWidget>
#include "Report/Inventory/CurrentInventoryGroupsTVModel.h"
#include "Report/Inventory/CurrentInventoryGroupsDialogView.h"
#include "Report/ReportDialogController.h"
class CurrentInventoryGroupsDialogView;

class CurrentInventoryGroupsDialogController : public ReportDialogController
{
    Q_OBJECT
private:
    CurrentInventoryGroupsDialogView *view;
    CurrentInventoryGroupsTVModel *tvModel;

    void restoreTableState();
    void saveTableState();
public:
    explicit CurrentInventoryGroupsDialogController(QWidget *parent);
    ~CurrentInventoryGroupsDialogController();

    void exec();

public slots:
    void showWithZeroQuantity(bool checked);
    void printReport();
};

#endif // CURRENTINVENTORYGROUPSDIALOGCONTROLLER_H
