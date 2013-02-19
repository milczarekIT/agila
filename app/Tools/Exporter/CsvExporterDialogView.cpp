#include "CsvExporterDialogView.h"

CsvExporterDialogView::CsvExporterDialogView(CsvExporterDialogController *controller, QStringList availableColumns, QWidget *parent)
    : QDialog(parent)
{
    this->controller = controller;
    this->availableColumns = availableColumns;
    this->setMinimumSize(900, 600);
    this->setLayout(layout = new QGridLayout());

    initComponents();
    initConnections();
}

void CsvExporterDialogView::initComponents() {
    initCheckboxes();
    initTable();
    initButtonBox();
}

void CsvExporterDialogView::initCheckboxes() {
    groupBox = new QGroupBox ("Wybierz kolumny", this);
    checkBoxesGroup = new QButtonGroup(this);
    checkBoxesGroup->setExclusive(false);

    // create checkBox
    QCheckBox *checkBox;
    for(int id = 0; id < availableColumns.size(); id++) {
        QString text = availableColumns.at(id);
        checkBox = new QCheckBox(text);
        checkBoxesGroup->addButton(checkBox, id);

        if(controller->getDefaultChecked().contains(text))
            checkBox->setChecked(true);
    }

    QGridLayout *layout = new QGridLayout();
    checkBoxList = (QList<QAbstractButton*>) checkBoxesGroup->buttons();

    // add checkbox to layout
    int numberOfButtonColumns = 5;
    int buttonsPerColumn = qCeil(checkBoxList.size()/numberOfButtonColumns);

    for(int i = 0, row = 0, column = 0; i < checkBoxList.size(); i++) {
        if(i%buttonsPerColumn == 0) {
            column++;
            row = 0;
        }
        else
            row++;

        layout->addWidget(checkBoxList.at(i), row, column);
    }

    groupBox->setLayout(layout);

    this->layout->addWidget(groupBox, 0, 0);
    this->layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
}

void CsvExporterDialogView::initTable() {
    tableWidget = new QTableWidget(0, availableColumns.size());

    for(int i = 0; i < availableColumns.size(); i++)
        tableWidget->setHorizontalHeaderItem(i, new QTableWidgetItem(availableColumns.at(i)));

    for(int i = 0; i < checkBoxList.size(); i++) {
        if(!checkBoxList.at(i)->isChecked())
            tableWidget->setColumnHidden(i, true);
    }
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setSelectionMode(QAbstractItemView::NoSelection);

    this->layout->addWidget(tableWidget, 1, 0);
}

void CsvExporterDialogView::initButtonBox() {
    buttonBox = new QDialogButtonBox(this);
    buttonBox->addButton("Anuluj", QDialogButtonBox::RejectRole);
    buttonBox->addButton("Eksportuj do pliku", QDialogButtonBox::AcceptRole);

    this->layout->addWidget(buttonBox, 2,0, Qt::AlignRight);
}

void CsvExporterDialogView::initConnections() {
    connect(checkBoxesGroup, SIGNAL(buttonClicked(int)), controller, SLOT(checkBoxClicked(int)));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(buttonBox, SIGNAL(accepted()), controller, SLOT(exportToFile()));
}

QButtonGroup *CsvExporterDialogView::getCheckBoxesGroup() {
    return checkBoxesGroup;
}

QList<QAbstractButton*> CsvExporterDialogView::getCheckBoxList() {
    return checkBoxList;
}

QTableWidget *CsvExporterDialogView::getTableWidget() {
    return tableWidget;
}

