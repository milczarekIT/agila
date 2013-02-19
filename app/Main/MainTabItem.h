#ifndef MAINTABITEM_H
#define MAINTABITEM_H

#include <QWidget>
#include <QGridLayout>
#include "Components/Button.h"
#include "Components/TableView.h"
#include "Other/Application/ModuleManager.h"

class MainTabItem : public QWidget
{
    Q_OBJECT
private:
    void setOptions();

protected:
    QGridLayout *layout;
    TableView *tableView;
    Button* buttonSelectColumns;

public:
    explicit MainTabItem();
    ~MainTabItem();
    QGridLayout *getLayout();

    virtual TableView* getTableView();

};

#endif // MAINTABITEM_H
