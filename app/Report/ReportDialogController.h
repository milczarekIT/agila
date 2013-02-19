#ifndef REPORTDIALOGCONTROLLER_H
#define REPORTDIALOGCONTROLLER_H

#include <QWidget>
#include <QHeaderView>
#include "Other/ITableStateManager.h"
#include "Components/MessageBox.h" //usun
#include "Other/Application/ApplicationManager.h" //usun

class ReportDialogController : public QObject, public ITableStateManager
{
    Q_OBJECT
public:
    ReportDialogController();

    virtual void exec() = 0;

public slots:
    virtual void printReport() = 0;
};

#endif // REPORTDIALOGCONTROLLER_H
