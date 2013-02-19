#include "MainStoreComboBox.h"

MainStoreComboBox::MainStoreComboBox(MainStoreComboBoxController *controller)
{
    this->controller = controller;
    setConnections();
    setOptions();
}

void MainStoreComboBox::setOptions()
{
    this->setGeometry(QRect(165, 5, 150, 0));
    this->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    this->setStatusTip("Przełącz magazyn");
    this->setCursor((QCursor(Qt::PointingHandCursor)));
}

void MainStoreComboBox::setConnections()
{
    connect(this, SIGNAL(currentIndexChanged(int)), controller, SLOT(switchStore(int)));
}
