#include "GoodsRemoveConfirmativeDialog.h"

GoodsRemoveConfirmativeDialog::GoodsRemoveConfirmativeDialog(int id, QWidget *parent) : QDialog(parent)
{
    service = new GoodsService();
    idGood = id;
    initView();
    initConnections();
}

void GoodsRemoveConfirmativeDialog::initView() {
    this->setLayout(layout = new QGridLayout());
    this->setWindowTitle("Czy na pewno usunąć towar?");

    buttonsLayout = new QHBoxLayout();

    if(service->isGoodOnlyAtActualWarehouse(idGood))
        initViewForGoodOnlyAtActualWarehouse();
    else
        initViewForGoodsInFewWarehouses();
    layout->addLayout(buttonsLayout, 1, 0, Qt::AlignRight);
  }

void GoodsRemoveConfirmativeDialog::initViewForGoodOnlyAtActualWarehouse() {

    layout->addWidget(text = new QLabel("Czy na pewno usunąć towar?\n\n"));
    removeButton = new QPushButton("Usuń");
    cancelButton = new QPushButton("Anuluj");

    buttonsLayout->addWidget(removeButton);
    buttonsLayout->addWidget(cancelButton);
}

void GoodsRemoveConfirmativeDialog::initViewForGoodsInFewWarehouses() {

    layout->addWidget(text = new QLabel("Towar/usługa znajduje się w więcej niż jednym magazynie. Czy na pewno usunąć towar/usługę?\n"));
    removeButton = new QPushButton("Usuń z tego magazynu");
    removeAllButton = new QPushButton("Usuń z wszystkich magazynów");
    cancelButton = new QPushButton("Anuluj");

    buttonsLayout->addWidget(removeButton);
    buttonsLayout->addWidget(removeAllButton);
    buttonsLayout->addWidget(cancelButton);

    connect(removeAllButton, SIGNAL(clicked()), this, SLOT(removeGoodFromAllWarehouses()));
}

void GoodsRemoveConfirmativeDialog::initConnections() {
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeGood()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

void GoodsRemoveConfirmativeDialog::removeGood() {
    service->removeGood(idGood);
    this->close();
}

void GoodsRemoveConfirmativeDialog::removeGoodFromAllWarehouses() {
    service->removeGoodFromAllWarehouses(idGood);
    this->close();
}
