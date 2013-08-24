#include "ReportListDialogController.h"

ReportListDialogController::ReportListDialogController(Report::ReportType type, QWidget *parent)
{
    this->type = type;
    view = new ReportListDialogView(parent, this);
    qDebug() << "ReportListDialogController::type: " << type;
    view->setWindowTitle("Type");

    tvModel = new ReportListTVModel();

    tvModel->setReportTypeFilter(type);
    tvModel->getData();
    view->setTVModel(tvModel);
}

void ReportListDialogController::exec() {
    view->exec();
}

void ReportListDialogController::handleMenuAction(QAction *action) {
    qDebug() << "actionName: __ " << action->property("actionName");
}
