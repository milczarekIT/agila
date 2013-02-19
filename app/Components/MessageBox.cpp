#include "MessageBox.h"

MessageBox::MessageBox(QWidget *parent) : QMessageBox(parent)
{
}


QString MessageBox::INFORMATIVE_TEXT= "Czy chcesz zapisac/kontynuowac?";


int MessageBox::createQuestionBox(QString text, QString informativeText, Icon icon)
{
     this->setText(text); // zmienic rozmiar message boxa

     this->setInformativeText(informativeText);
     this->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
     this->setDefaultButton(QMessageBox::Yes);
     this->setButtonText(QMessageBox::Yes,"Tak");
     this->setButtonText(QMessageBox::No,"Nie");
     this->setIcon(icon);
     int ret = this->exec();

     if (ret == QMessageBox::Yes)
         return MessageBox::YES;
     else if (ret == QMessageBox::No)
         return MessageBox::N0;
     else
         return 0;
}


void MessageBox::createInfoBox(QString text)
{
     this->setText(text);
     this->setInformativeText("");
     this->setStandardButtons(QMessageBox::Ok);
     this->setIcon(QMessageBox::Information);
     this->exec();
}

void MessageBox::createWarningBox(QString text)
{
     this->setText(text);
     this->setInformativeText("");
     this->setStandardButtons(QMessageBox::Ok);
     this->setIcon(QMessageBox::Warning);
     this->exec();
}
