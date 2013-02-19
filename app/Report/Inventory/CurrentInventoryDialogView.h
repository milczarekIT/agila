#ifndef CURRENTINVENTORYDIALOGVIEW_H
#define CURRENTINVENTORYDIALOGVIEW_H

#include "Report/Inventory/CurrentInventoryTVModel.h"
#include "Report/Inventory/CurrentInventoryDialogController.h"
#include "Report/Inventory/InventoryDialogView.h"
class CurrentInventoryDialogController;

class CurrentInventoryDialogView : public InventoryDialogView
{
private:
    CurrentInventoryDialogController *controller;
    CurrentInventoryTVModel *tvModel;

public:
    CurrentInventoryDialogView(QWidget *parent, CurrentInventoryDialogController *controller);
    ~CurrentInventoryDialogView();

    void setTVModel(TVModel *model);
};

#endif // CURRENTINVENTORYDIALOGVIEW_H
