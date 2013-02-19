#include "MainTabItem.h"

MainTabItem::MainTabItem() {
    buttonSelectColumns = new Button(ButtonStruct("Wybierz kolumny","Wybierz kolumny, które ma zawierać aktualna tabela", QSize(144,28)));
    setOptions();
}

void MainTabItem::setOptions() {
    this->setLayout(layout = new QGridLayout());
    //this->setMaximumHeight(170);
}

QGridLayout *MainTabItem::getLayout() {
    return layout;
}

MainTabItem::~MainTabItem() {
    delete layout;
}

TableView* MainTabItem::getTableView() {
    return tableView;
}


