#include "TopGoodsDialogView.h"

TopGoodsDialogView::TopGoodsDialogView(QWidget *parent, TopGoodsDialogController *controller)
    : ReportDialogView(parent)
{
    this->controller = controller;
    this->setWindowTitle("Najlepiej sprzedające się towary");

    this->addComponents();

    connect(buttonBox, SIGNAL(accepted()), controller, SLOT(printReport()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(spinBoxListLimit, SIGNAL(valueChanged(int)), controller, SLOT(setListLimitFilter(int)));
    connect(dateEditFrom, SIGNAL(dateChanged(QDate)), controller, SLOT(setDateFromFilter(QDate)));
    connect(dateEditTo, SIGNAL(dateChanged(QDate)), controller, SLOT(setDateToFilter(QDate)));
}

void TopGoodsDialogView::addComponents()
{
    tableView = new QTableView;
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setFocusPolicy(Qt::NoFocus);

    layout->setRowMinimumHeight(0, 20);

    spinBoxListLimit = new QSpinBox();
    spinBoxListLimit->setMinimum(1);
    spinBoxListLimit->setValue(20);

    dateEditFrom = new DateEdit();
    dateEditTo = new DateEdit();
    dateEditFrom->setDate(QDate(QDate::currentDate().year(), 1, 1));
    dateEditTo->setDate(QDate(QDate::currentDate().year(), 12, 31));

    layout->addWidget(new QLabel("Liczba towarów: "), 0, 1, 1, 1);
    layout->addWidget(spinBoxListLimit, 0, 2, 1, 1);
    layout->addWidget(new QLabel("Od: "), 0, 3, 1, 1);
    layout->addWidget(dateEditFrom, 0, 4, 1, 1);
    layout->addWidget(new QLabel("Do: "), 0, 5, 1, 1);
    layout->addWidget(dateEditTo, 0, 6, 1, 1);

    layout->addWidget(tableView, 1, 1, 1, 6);

    layout->addWidget(buttonBox, 2, 1, 1, 6, Qt::AlignRight);
}

void TopGoodsDialogView::setTVModel(TVModel *model)
{
    tableView->setModel(model);
    tableView->setColumnHidden(0, true);
    tableView->setColumnWidth(1, 140);
    tableView->setColumnWidth(2, 290);
    tableView->setColumnWidth(3, 100);
    tableView->setColumnWidth(4, 65);
    tableView->setColumnWidth(5, 85);
    tableView->setColumnWidth(6, 85);
    tableView->setColumnWidth(7, 85);

}

QSpinBox *TopGoodsDialogView::getSpinBoxListLimit()
{
    return spinBoxListLimit;
}

DateEdit *TopGoodsDialogView::getDateEditFrom()
{
    return dateEditFrom;
}

DateEdit *TopGoodsDialogView::getDateEditTo()
{
    return dateEditTo;
}
