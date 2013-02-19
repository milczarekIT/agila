#ifndef MAINTABOTHERDOCUMENTSITEM_H
#define MAINTABOTHERDOCUMENTSITEM_H

#include <QLabel>
#include <QComboBox>
#include "Components/Button.h"
#include "Main/MainTabItem.h"
#include "Components/DateEdit.h"
#include "Components/TableView.h"
#include "Main/MainTabOtherDocumentsItemController.h"
class MainTabOtherDocumentsItemController;

class MainTabOtherDocumentsItem : public MainTabItem
{

private:
    Button *addNK;
    QComboBox *otherDocuments;
    DateEdit *otherDocFrom;
    DateEdit *otherDocTo;
    TableView *tableView;
    MainTabOtherDocumentsItemController *controller;
    void setInterface();
    void setConnections();

public:
    MainTabOtherDocumentsItem(MainTabOtherDocumentsItemController *controller);
    Button *getAddNK();
    QComboBox *getOtherDocuments();
    DateEdit *getOtherDocFrom();
    DateEdit *getOtherDocTo();
    TableView *getTableView();
};

#endif // MAINTABOTHERDOCUMENTSITEM_H
