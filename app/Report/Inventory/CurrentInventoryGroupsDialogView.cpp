#include "CurrentInventoryGroupsDialogView.h"

CurrentInventoryGroupsDialogView::CurrentInventoryGroupsDialogView(QWidget *parent, CurrentInventoryGroupsDialogController *controller)
    : InventoryDialogView(parent)
{
    this->controller = controller;
    this->setWindowTitle("Remanent bieżący wg grup");

    addComponents();

    connect(checkBoxShowWithZeroQuantity, SIGNAL(clicked(bool)), controller, SLOT(showWithZeroQuantity(bool)));
    connect(buttonBox, SIGNAL(accepted()), controller, SLOT(printReport()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

CurrentInventoryGroupsDialogView::~CurrentInventoryGroupsDialogView()
{
}

void CurrentInventoryGroupsDialogView::setTVModel(TVModel *model) {
    tableView->setModel(model);
    tableView->setColumnWidth(0, 300);
    tableView->setColumnWidth(1, 250);
    tableView->setColumnWidth(2, 300);
}
