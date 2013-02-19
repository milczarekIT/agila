#include "WarehouseDialogView.h"

WarehouseDialogView::WarehouseDialogView(WarehouseDialogController *controller, QWidget *parent) : QDialog(parent)
{
    this->controller = controller;
    this->setMinimumSize(430, 150);
    this->layout = new QGridLayout();
    layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    this->setLayout(layout);

    initComponents();
    initConnections();
}

void WarehouseDialogView::initComponents() {
    layout->addWidget(new QLabel("Nazwa magazynu: "), 0, 0);
    layout->addWidget(lineName = new QLineEdit(), 0, 1, 1, 4);
    lineName->setMinimumWidth(150);
    layout->addWidget(lineNameNotAvailable = new QLabel("<font color=\"red\">Zajęta</font>"), 0, 6);
    lineNameNotAvailable->hide();
    layout->addWidget(new QLabel("Krótka nazwa: "), 1, 0);
    layout->addWidget(lineShortName = new QLineEdit(), 1, 1);
    lineShortName->setMaxLength(4);
    lineShortName->setMaximumWidth(60);
    layout->addWidget(lineShortNameNotAvailable = new QLabel("<font color=\"red\">Zajęta</font>"), 1, 6);
    lineShortNameNotAvailable->hide();
    layout->addWidget(new QLabel("Domyślny: "), 2, 0);
    layout->addWidget(checkBoxDefault = new QCheckBox(), 2,1);

    groupBox = new QGroupBox("Zaznacz magazyn, z którego importować towary");
    QVBoxLayout *radioButtonsLayout = new QVBoxLayout();
    buttonGroup = new QButtonGroup();
    QRadioButton* radioButton = new QRadioButton("Żaden");
    radioButton->setChecked(true);
    buttonGroup->addButton(radioButton, 0);
    radioButtonsLayout->addWidget(radioButton);

    WarehouseService *whService = new WarehouseService();
    QVector<Warehouse> warehouses = whService->getWarehouses();
    delete whService;
    for(int i = 0; i < warehouses.size(); i++) {
        radioButton = new QRadioButton(warehouses[i].getName());
        buttonGroup->addButton(radioButton, warehouses[i].getId());

        radioButtonsLayout->addWidget(radioButton);
    }

    groupBox->setLayout(radioButtonsLayout);
    groupBox->setMinimumWidth(400);
    layout->addWidget(groupBox, 3, 0, 1, 4, Qt::AlignHCenter);

    layout->addWidget(buttonBox = new ButtonBox(this), 9, 0, 1, 10, Qt::AlignRight);
}

void WarehouseDialogView::initConnections() {
    connect(lineName, SIGNAL(textChanged(QString)), controller, SLOT(suggestShortName(QString)));
    connect(lineName, SIGNAL(textChanged(QString)), controller, SLOT(checkIfAvailableName(QString)));
    connect(lineShortName, SIGNAL(textChanged(QString)), controller, SLOT(checkIfAvailableShortName(QString)));
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

QLineEdit *WarehouseDialogView::getLineName() {
    return lineName;
}

QLineEdit *WarehouseDialogView::getLineShortName() {
    return lineShortName;
}

QCheckBox *WarehouseDialogView::getCheckBoxDefault() {
    return checkBoxDefault;
}

QGroupBox *WarehouseDialogView::getGroupBox() {
    return groupBox;
}

QButtonGroup* WarehouseDialogView::getButtonsImportWarehouse() {
    return buttonGroup;
}

QLabel *WarehouseDialogView::getLineNameNotAvailable() {
    return lineNameNotAvailable;
}

QLabel *WarehouseDialogView::getLineShortNameNotAvailable() {
    return lineShortNameNotAvailable;
}




