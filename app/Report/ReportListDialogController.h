#ifndef REPORTLISTDIALOGCONTROLLER_H
#define REPORTLISTDIALOGCONTROLLER_H

#include "ReportListDialogView.h"
#include "Report.h"
#include "ReportListTVModel.h"
class ReportListDialogView;

class ReportListDialogController : public QObject
{
    Q_OBJECT
private:
    ReportListDialogView *view;
    Report::ReportType type;
    ReportListTVModel *tvModel;
public:
    ReportListDialogController(Report::ReportType type, QWidget *parent = 0);

    void exec();

public slots:
    void handleMenuAction(QAction *action);
};

#endif // REPORTLISTDIALOGCONTROLLER_H
