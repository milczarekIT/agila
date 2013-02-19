#include "ButtonsList.h"

ButtonsList::ButtonsList(QWidget *parent) :
    QComboBox(parent)
{
    tV = new QListView();
    model = new QStandardItemModel(0,1);

    this->setMinimumSize(260,50);
    this->setMaximumSize(260,50);

    this->setView(tV);
    this->setModel(model);
    this->setIconSize(QSize(35,35));
    tV->setIconSize(QSize(35,35));

    row = 0;
    col = 0;
}

void ButtonsList::addItem(const QString &text, QString status, QString icon)
{
    QStandardItem *item = new QStandardItem(text);
    item->setIcon(QIcon(":/image-theme/"+ icon + ".png"));
    item->setStatusTip(status);
    item->setSizeHint(QSize(140,50));
    model->setItem(row++,col,item);
}

QStandardItemModel *ButtonsList::getModel() { return model; }
QListView *ButtonsList::getTableView() { return tV; }
