#include "UnrealizedOrderDialogView.h"

UnrealizedOrderDialogView::UnrealizedOrderDialogView(QWidget *parent, UnrealizedOrderDialogController *controller)
    : ReportDialogView(parent)
{
    this->controller = controller;
    this->setWindowTitle("Niezrealizowane zamówienia");

    this->addComponents();

    connect(buttonBox, SIGNAL(accepted()), controller, SLOT(printReport()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void UnrealizedOrderDialogView::addComponents() {

    tableView = new QTableView;
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setFocusPolicy(Qt::NoFocus);

    labelValue = new QLabel("Wartość brutto: ");
    labelValue->setAlignment(Qt::AlignRight);

    lineValue = new QLineEdit();

    layout->setRowMinimumHeight(0, 20);
    layout->addWidget(tableView, 0, 1, 1, 4);

    layout->addWidget(labelValue, 1, 3, Qt::AlignRight);
    layout->addWidget(lineValue, 1, 4, Qt::AlignRight);
    layout->addWidget(buttonBox, 2, 1, 1, 4, Qt::AlignRight);
}


void UnrealizedOrderDialogView::setTVModel(TVModel *model)
{
    tableView->setModel(model);
    tableView->setColumnWidth(0, 115);
    tableView->setColumnWidth(1, 300);
    tableView->setColumnWidth(2, 140);
    tableView->setColumnWidth(3, 140);
    tableView->setColumnWidth(4, 135);
}
