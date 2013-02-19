#include "SettingsAbstractItemView.h"

SettingsAbstractItemView::SettingsAbstractItemView(QWidget *parent) : QWidget(parent) {
    this->setLayout(mainLayout = new QGridLayout());
    messageBox = new MessageBox(parent);
}

void SettingsAbstractItemView::emitChangesWereMade() {
    emit changesWereMade();
}

MessageBox *SettingsAbstractItemView::getMessageBox() {
    return messageBox;
}
