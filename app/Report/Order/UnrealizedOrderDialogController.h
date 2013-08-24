#ifndef UNREALIZEDORDERDIALOGCONTROLLER_H
#define UNREALIZEDORDERDIALOGCONTROLLER_H

#include "Report/ReportDialogController.h"
#include "Report/Order/UnrealizedOrderDialogView.h"
#include "Report/Order/UnrealizedOrderTVModel.h"
class UnrealizedOrderDialogView;

class UnrealizedOrderDialogController : public ReportDialogController
{
    UnrealizedOrderDialogView *view;
    UnrealizedOrderTVModel *tvModel;
    QString type; // ZK or ZD

    void restoreTableState();
    void saveTableState();

public:
    UnrealizedOrderDialogController(QWidget *parent, QString type);
    ~UnrealizedOrderDialogController();

    void exec();

public slots:
    void saveReport();
};

#endif // UNREALIZEDORDERDIALOGCONTROLLER_H
