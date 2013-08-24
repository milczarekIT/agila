#include "UnpaidDocumentDialogView.h"

UnpaidDocumentDialogView::UnpaidDocumentDialogView(QWidget *parent, UnpaidDocumentDialogController *controller)
    : QDialog(parent)
{
    this->controller = controller;
    this->setWindowTitle("Niezapłacone dokumenty");

    addComponents();

    connect(buttonBox, SIGNAL(accepted()), controller, SLOT(saveReport()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(checkBoxOnlyNotPaidOnTime, SIGNAL(clicked(bool)), controller, SLOT(showOnlyNotPaidOnTime(bool)));
}

UnpaidDocumentDialogView::~UnpaidDocumentDialogView() {}

void UnpaidDocumentDialogView::setTVModel(TVModel *tvModel)
{
    tableView->setModel(tvModel);
}

void UnpaidDocumentDialogView::initTVColumnWidhts()
{
    tableView->setColumnWidth(0, 110);
    tableView->setColumnWidth(1, 220);
    tableView->setColumnWidth(2, 120);
    tableView->setColumnWidth(3, 120);
    tableView->setColumnWidth(4, 110);
    tableView->setColumnWidth(5, 170);
}

void UnpaidDocumentDialogView::addComponents()
{
    this->setLayout(layout = new QGridLayout());
    this->setMinimumSize(900,600);

    checkBoxOnlyNotPaidOnTime = new QCheckBox("Tylko z przekrzoczonym terminem");


    tableView = new QTableView;
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->verticalHeader()->setDefaultSectionSize(20);

    labelValue = new QLabel("Wartość netto: ");
    labelValue->setAlignment(Qt::AlignRight);

    lineValue = new QLineEdit();

    layout->addWidget(checkBoxOnlyNotPaidOnTime, 0, 1, 1, 4);
    layout->addWidget(tableView, 1, 1, 1, 4);

    layout->addWidget(labelValue, 2, 3, Qt::AlignRight);
    layout->addWidget(lineValue, 2, 4, Qt::AlignRight);

    buttonBox = new QDialogButtonBox(Qt::Horizontal, this);
    buttonBox->addButton("Anuluj", QDialogButtonBox::RejectRole);
    buttonBox->addButton("Zapisz", QDialogButtonBox::AcceptRole);
    layout->addWidget(buttonBox, 3, 1, 1, 4, Qt::AlignRight);
}


QLineEdit* UnpaidDocumentDialogView::getLineValue()
{
    return this->lineValue;
}

QTableView *UnpaidDocumentDialogView::getTableView()
{
    return this->tableView;
}
