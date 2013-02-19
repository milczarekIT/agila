#include "InventoryDialogView.h"

InventoryDialogView::InventoryDialogView(QWidget *parent) : ReportDialogView(parent)
{
}

QCheckBox* InventoryDialogView::getCheckBoxShowWithZeroQuantity() {
    return checkBoxShowWithZeroQuantity;
}

void InventoryDialogView::addComponents()
{
    checkBoxShowWithZeroQuantity = new QCheckBox("Pokaż z zerowym stanem");
    checkBoxShowWithZeroQuantity->setChecked(true);
    checkBoxShowWithZeroQuantity->setFocusPolicy(Qt::NoFocus);

    tableView = new QTableView;
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setFocusPolicy(Qt::NoFocus);

    labelValue = new QLabel("Wartość netto: ");
    labelValue->setAlignment(Qt::AlignRight);

    lineValue = new QLineEdit();

    layout->setRowMinimumHeight(0, 20);
    layout->addWidget(checkBoxShowWithZeroQuantity, 0, 1, 1, 4);
    layout->addWidget(tableView, 1, 1, 1, 4);

    layout->addWidget(labelValue, 2, 3, Qt::AlignRight);
    layout->addWidget(lineValue, 2, 4, Qt::AlignRight);
    layout->addWidget(buttonBox, 3, 1, 1, 4, Qt::AlignRight);
}
