#include "ButtonBox.h"

ButtonBox::ButtonBox(QWidget *parent) : QDialogButtonBox(parent)
{
    this->setMinimumHeight(25);
    this->addButton("Anuluj", QDialogButtonBox::RejectRole);
    this->addButton("Zapisz", QDialogButtonBox::AcceptRole);
    this->setMinimumHeight(25);
}
