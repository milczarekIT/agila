#include "ArchiverDialogView.h"

ArchiverDialogView::ArchiverDialogView(QWidget *parent, ArchiverDialogController *controller) : QDialog(parent)
{
    this->setWindowTitle("Archiwizacja");
    this->controller = controller;

    mainLayout = new QGridLayout();
    this->setLayout(mainLayout);

    initRadioButtons();
    initButtons();
    initTable();
    initOther();
    initConnections();
    addAllComponents();
}

void ArchiverDialogView::initRadioButtons()
{
    groupRemind = new QGroupBox("Przypomnienia", this);
    radioRemind = new QRadioButton("Przyminaj o tworzeniu kopii bezpieczeństwa co");
    radioDontRemind = new QRadioButton("Nie przypominaj");

    groupRemoveOld = new QGroupBox("Usuwanie starych wersji", this);
    radioRemove = new QRadioButton("Usuwaj stare kopie bezpieczeństwa po");
    radioDontRemove = new QRadioButton("Nie usuwaj");

}

void ArchiverDialogView::initOther()
{
    spinRemind = new QSpinBox();
    spinRemind->setRange(0, 365);
    spinRemove = new QSpinBox();
    spinRemove->setRange(0, 365);

    labelRemind = new QLabel("dni");
    labelRemove = new QLabel("dniach");
}

void ArchiverDialogView::initButtons()
{
    buttonCreate = new QPushButton("Stwórz");
    buttonRestore = new QPushButton("Przywróć");
    buttonRemove = new QPushButton("Usuń");

    buttonBox = new ButtonBox(this);
}

void ArchiverDialogView::initTable()
{
    table = new QTableView();
    tableModel=new QStandardItemModel();

    QStringList tableHeaders; tableHeaders <<"Nazwa pliku"<< "Rozmiar"<<"Utworzono";
    tableModel->setHorizontalHeaderLabels(tableHeaders);
    table->setModel(tableModel);
    table->setColumnWidth(0,250);
    table->setColumnWidth(1,100);
    table->setColumnWidth(2,150);
    table->verticalHeader()->setDefaultSectionSize(20);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);;
    table->horizontalHeader()->setStretchLastSection(true);
    table->horizontalHeader()->setMaximumHeight(20);

    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
}

void ArchiverDialogView::initConnections()
{
    connect(spinRemind, SIGNAL(valueChanged(int)), controller, SLOT(changesAtSpinRemind(int)));
    connect(spinRemove, SIGNAL(valueChanged(int)), controller, SLOT(changesAtSpinRemove(int)));
    connect(buttonCreate, SIGNAL(clicked()), controller, SLOT(createBackup()));
    connect(buttonRestore, SIGNAL(clicked()), controller, SLOT(restoreBackup()));
    connect(buttonRemove, SIGNAL(clicked()), controller, SLOT(removeBackup()));
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void ArchiverDialogView::addAllComponents()
{
    QGridLayout *box = new QGridLayout;
    box->addWidget(radioRemind, 0, 0);
    box->addWidget(spinRemind, 0, 1);
    box->addWidget(labelRemind, 0, 2);
    box->addWidget(radioDontRemind, 1, 0);
    groupRemind->setLayout(box);
    mainLayout->addWidget(groupRemind, 0, 0, 1, 2);

    QGridLayout *box2 = new QGridLayout;
    box2->addWidget(radioRemove, 0, 0);
    box2->addWidget(spinRemove, 0, 1);
    box2->addWidget(labelRemove, 0, 2);
    box2->addWidget(radioDontRemove, 1, 0);
    groupRemoveOld->setLayout(box2);
    mainLayout->addWidget(groupRemoveOld, 1, 0, 1, 2);

    mainLayout->addWidget(buttonCreate, 2, 0);
    mainLayout->addWidget(buttonRestore, 2, 1);
    mainLayout->addWidget(buttonRemove, 2, 2);

    mainLayout->addWidget(table,3,0,4,4);

    mainLayout->addWidget(buttonBox, 7, 0, 1, 3, Qt::AlignRight);
}

QString ArchiverDialogView::getSelectedFileName()
{
    QModelIndex index = table->currentIndex();
    int row = index.row();

    if(row != -1)
        return tableModel->data(index.model()->index(row,0)).toString();
    else
        return "";
}

QRadioButton *ArchiverDialogView::getRadioRemind() { return radioRemind; }
QRadioButton *ArchiverDialogView::getRadioDontRemind() { return radioDontRemind; }
QRadioButton *ArchiverDialogView::getRadioRemove() { return radioRemove; }
QRadioButton *ArchiverDialogView::getRadioDontRemove() {return radioDontRemove; }
QSpinBox *ArchiverDialogView::getSpinRemind() { return spinRemind; }
QSpinBox *ArchiverDialogView::getSpinRemove() { return spinRemove; }
QTableView *ArchiverDialogView::getTable() { return table; }
QStandardItemModel *ArchiverDialogView::getTableModel() { return tableModel; }


ArchiverDialogView::~ArchiverDialogView()
{
    delete radioRemind;
    delete spinRemind;
    delete radioDontRemind;
    delete groupRemind;

    delete radioRemove;
    delete spinRemove;
    delete radioDontRemove;
    delete groupRemoveOld;

    delete buttonCreate;
    delete buttonRestore;
    delete buttonRemove;
    delete buttonBox;

    delete table;
    delete tableModel;

    delete mainLayout;
}

