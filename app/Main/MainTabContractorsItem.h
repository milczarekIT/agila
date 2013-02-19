#ifndef MAINTABCONTRACTORSSITEM_H
#define MAINTABCONTRACTORSSITEM_H

#include <QLabel>
#include <QString>
#include <QComboBox>
#include <QLineEdit>
#include "Components/Button.h"
#include "Main/MainTabItem.h"
#include "Components/TableView.h"
#include "Main/MainTabContractorsItemController.h"
class MainTabContractorsItemController;

class MainTabContractorsItem : public MainTabItem
{

private:
    Button *addCon;
    Button *editCon;
    Button *deleteCon;
    QComboBox *consGroup;
    QComboBox *contractorType;
    QLineEdit *conFilterSymbol;
    QLineEdit *conFilterName;
    QLineEdit *conFilterNIP;
    MainTabContractorsItemController *controller;
    void setInterface();
    void setConnections();
    void setMenu();

public:
    MainTabContractorsItem(MainTabContractorsItemController *controller);
    Button *getAddCon();
    Button *getEditCon();
    Button *getDeleteCon();
    QComboBox *getConGroup();
    QComboBox *getContractorType();
    QLineEdit *getConFilterSymbol();
    QLineEdit *getConFilterName();
    QLineEdit *getConFilterNIP();
};

#endif // MAINTABCONTRACTORSSITEM_H
