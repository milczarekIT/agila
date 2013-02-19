#ifndef CURRENTINVENTORYGROUPSDIALOGVIEW_H
#define CURRENTINVENTORYGROUPSDIALOGVIEW_H

#include <QDialog>
#include <QGridLayout>
#include <QCheckBox>
#include <QTableView>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include "Report/Inventory/CurrentInventoryTVModel.h"
#include "Report/Inventory/CurrentInventoryGroupsDialogController.h"
#include "Report/Inventory/InventoryDialogView.h"
class CurrentInventoryGroupsDialogController;

class CurrentInventoryGroupsDialogView : public InventoryDialogView
{
private:
    CurrentInventoryGroupsDialogController *controller;
    CurrentInventoryTVModel *tvModel;

public:
    CurrentInventoryGroupsDialogView(QWidget *parent, CurrentInventoryGroupsDialogController *controller);
    ~CurrentInventoryGroupsDialogView();

    void setTVModel(TVModel *model);
};

#endif // CURRENTINVENTORYGROUPSDIALOGVIEW_H
