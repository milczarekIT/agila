#include "EndingGoodsDialogView.h"

EndingGoodsDialogView::EndingGoodsDialogView(QWidget *parent, EndingGoodsDialogController *controller)
    : ReportDialogView(parent)
{
    this->controller = controller;
    this->setWindowTitle("Kończące się towary");

    this->addComponents();

    connect(buttonBox, SIGNAL(accepted()), controller, SLOT(printReport()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void EndingGoodsDialogView::addComponents()
{
    tableView = new QTableView;
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setFocusPolicy(Qt::NoFocus);

    labelText = new QLabel("Ilość nie większa niż:");
    spinBoxQuantity = new QDoubleSpinBox();
    spinBoxQuantity->setMinimum(0.0);
    spinBoxQuantity->setDecimals(3);
    spinBoxQuantity->setValue(3.00);

    layout->setRowMinimumHeight(0, 20);

    layout->addWidget(labelText, 0, 1, 1, 1);
    layout->addWidget(spinBoxQuantity, 0, 2, 1, 1);

    layout->addWidget(tableView, 1, 1, 1, 6);

    layout->addWidget(buttonBox, 2, 1, 1, 6, Qt::AlignRight);


    connect(spinBoxQuantity, SIGNAL(valueChanged(double)), controller, SLOT(quantityChanged(double)));
}

void EndingGoodsDialogView::setTVModel(TVModel *model)
{
    tableView->setModel(model);
    tableView->setColumnHidden(0, true);
    tableView->setColumnWidth(1, 170);
    tableView->setColumnWidth(2, 260);
    tableView->setColumnWidth(3, 80);
    tableView->setColumnWidth(4, 40);
    tableView->setColumnWidth(5, 120);
    tableView->setColumnWidth(6, 90);
    tableView->setColumnWidth(7, 90);
}

QDoubleSpinBox *EndingGoodsDialogView::getSpinBoxQuantity()
{
    return spinBoxQuantity;
}
