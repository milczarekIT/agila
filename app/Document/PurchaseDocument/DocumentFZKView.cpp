#include "DocumentFZKView.h"

DocumentFZKView::DocumentFZKView(QWidget *parent, DocumentFZKController *controller) : DocumentFKView(parent)
{
    this->controller = controller;
    this->mainLayout = new QGridLayout();

    this->setLayout(mainLayout);

    this->setMinimumSize(1024,768);
    if(controller->getEdition()==true)
        this->setWindowTitle("FZK - Edycja dokumentu");
    else
       this->setWindowTitle("FZK - Nowy dokument");
    initLineEdits();
    initButtons();
    initGoodsTable();
    initConnections();
    initTabs();
    addAllComponents(); //zawsze wywoływana po wszystkich inicjalizacjach!
    addAdditionalComopnent();

}

void DocumentFZKView::addAdditionalComopnent()
{
    linePurchaseDocSymbol = new QLineEdit();
    mainLayoutBeforeCorrection->addWidget(linePurchaseDocSymbol,3,5);
    mainLayoutBeforeCorrection->addWidget(new QLabel("Dla dok. nr :"),3,4);
}

