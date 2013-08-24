#include "CurrentInventoryDialogView.h"

CurrentInventoryDialogView::CurrentInventoryDialogView(QWidget *parent, CurrentInventoryDialogController *controller) :
    InventoryDialogView(parent)
{
    this->controller = controller;
    this->setWindowTitle("Remanent bieżący");

    addComponents();

    connect(checkBoxShowWithZeroQuantity, SIGNAL(clicked(bool)), controller, SLOT(showWithZeroQuantity(bool)));
    connect(buttonBox, SIGNAL(accepted()), controller, SLOT(saveReport()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}


CurrentInventoryDialogView::~CurrentInventoryDialogView()
{
}



void CurrentInventoryDialogView::setTVModel(TVModel *model)
{
    tableView->setModel(model);
    tableView->setColumnHidden(0, true);
    tableView->setColumnWidth(1, 220);
    tableView->setColumnWidth(2, 250);
    tableView->setColumnWidth(3, 120);
    tableView->setColumnWidth(4, 55);
    tableView->setColumnWidth(5, 65);
    tableView->setColumnWidth(6, 45);
    tableView->setColumnWidth(7, 170);
    tableView->setColumnWidth(8, 180);
}
