#ifndef MAINSTORECOMBOBOX_H
#define MAINSTORECOMBOBOX_H

#include <QComboBox>
#include "Main/MainStoreComboBoxController.h"
class MainStoreComboBoxController;

class MainStoreComboBox : public QComboBox
{
    Q_OBJECT

private:
    MainStoreComboBoxController *controller;
    void setOptions();
    void setConnections();

public:
    explicit MainStoreComboBox(MainStoreComboBoxController *controller);
};

#endif // MAINSTORECOMBOBOX_H
