#include "ReportDialogView.h"

ReportDialogView::ReportDialogView(QWidget *parent) : QDialog(parent)
{
    this->setLayout(layout = new QGridLayout());
    this->setMinimumSize(900,600);

    buttonBox = new QDialogButtonBox(Qt::Horizontal, this);
    buttonBox->addButton("Anuluj", QDialogButtonBox::RejectRole);
    buttonBox->addButton("Zapisz", QDialogButtonBox::AcceptRole);
}

QTableView* ReportDialogView::getTableView()
{
    return tableView;
}

QLineEdit* ReportDialogView::getLineValue() {
    return this->lineValue;
}
