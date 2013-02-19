#include "MissingGoodsDialogView.h"

MissingGoodsDialogView::MissingGoodsDialogView(QWidget *parent, MissingGoodsDialogController *controller)
    : ReportDialogView(parent)
{
    this->controller = controller;
    this->setWindowTitle("Brakujące towary");

    this->addComponents();

    connect(buttonBox, SIGNAL(accepted()), controller, SLOT(printReport()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void MissingGoodsDialogView::addComponents()
{
    tableView = new QTableView;
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setFocusPolicy(Qt::NoFocus);

    layout->setRowMinimumHeight(0, 20);
    layout->addWidget(tableView, 0, 1, 1, 4);

    layout->addWidget(buttonBox, 1, 1, 1, 4, Qt::AlignRight);
}

void MissingGoodsDialogView::setTVModel(TVModel *model)
{

    tableView->setModel(model);
    tableView->setColumnHidden(0, true);
    tableView->setColumnWidth(1, 210);
    tableView->setColumnWidth(2, 300);
    tableView->setColumnHidden(3, true);
    tableView->setColumnHidden(4, true);
    tableView->setColumnWidth(5, 140);
    tableView->setColumnWidth(6, 100);
    tableView->setColumnWidth(7, 100);

}
