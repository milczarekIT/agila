#ifndef MAINTABITEMCONTROLLER_H
#define MAINTABITEMCONTROLLER_H

#include <QWidget>
#include "Main/MainTabItem.h"

class MainTabItemController : public QWidget
{
    Q_OBJECT
public:
    MainTabItemController();

    virtual void initModel() = 0;
    virtual void refreshTable();

    virtual MainTabItem *getView() = 0;

    virtual ModuleManager::Module module() = 0;
};

#endif // MAINTABITEMCONTROLLER_H
