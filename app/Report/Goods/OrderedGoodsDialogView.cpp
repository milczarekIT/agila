#include "OrderedGoodsDialogView.h"

OrderedGoodsDialogView::OrderedGoodsDialogView(QWidget *parent, OrderedGoodsDialogController *controller)
    : ReportDialogView(parent)
{
    this->controller = controller;
    this->setWindowTitle("Zamówione towary");

    this->addComponents();

    connect(buttonBox, SIGNAL(accepted()), controller, SLOT(saveReport()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void OrderedGoodsDialogView::addComponents()
{
    tableView = new QTableView;
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setFocusPolicy(Qt::NoFocus);
    tableView->verticalHeader()->setDefaultSectionSize(20);

    layout->setRowMinimumHeight(0, 20);
    layout->addWidget(tableView, 0, 1, 1, 4);

    layout->addWidget(buttonBox, 1, 1, 1, 4, Qt::AlignRight);
}

void OrderedGoodsDialogView::setTVModel(TVModel *model)
{

    tableView->setModel(model);
    tableView->setColumnHidden(0, true);
    tableView->setColumnWidth(1, 160);
    tableView->setColumnWidth(2, 250);
    tableView->setColumnWidth(3, 55);
    tableView->setColumnWidth(4, 80);
    tableView->setColumnWidth(5, 35);
    tableView->setColumnWidth(6, 90);
    tableView->setColumnWidth(7, 90);
    tableView->setColumnWidth(8, 90);

}
