#ifndef REPORTLISTDIALOGVIEW_H
#define REPORTLISTDIALOGVIEW_H

#include <QDialog>
#include <QGridLayout>
#include <QTableView>
#include <QHeaderView>
#include <QMenu>
#include <QContextMenuEvent>
#include "Database/TVModel.h"
#include "ReportListDialogController.h"
class ReportListDialogController;

class ReportListDialogView : public QDialog
{
    ReportListDialogController *controller;

    QGridLayout *layout;
    QMenu *menu;
    QTableView *tableView;

    void addComponents();
    void addContextMenu();

protected:
    void contextMenuEvent(QContextMenuEvent * event);
public:
    ReportListDialogView(QWidget *parent, ReportListDialogController *controller);
    ~ReportListDialogView();

    void setTVModel(TVModel *model);


};

#endif // REPORTLISTDIALOGVIEW_H
