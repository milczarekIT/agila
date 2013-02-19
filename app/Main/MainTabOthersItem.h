#ifndef MAINTABOTHERSITEM_H
#define MAINTABOTHERSITEM_H

#include "Main/MainTabItem.h"
#include "Components/Button.h"
#include "Components/ToolButton.h"
#include "Main/MainTabOthersItemController.h"
class MainTabOthersItemController;

class MainTabOthersItem : public MainTabItem
{

private:
    Button *buttonHelp;
    Button *buttonArchiveSql;
    ToolButton *buttonExportGoodsToCsv;
    ToolButton *buttonExportContractorsToCsv;
    MainTabOthersItemController *controller;
    void setInterface();
    void setConnections();
    QWidget *setCentralPanel();

public:
    MainTabOthersItem(MainTabOthersItemController *controller);

};

#endif // MAINTABOTHERSITEM_H
