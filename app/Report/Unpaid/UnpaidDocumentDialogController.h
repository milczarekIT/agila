#ifndef UNPAIDDOCUMENTDIALOGCONTROLLER_H
#define UNPAIDDOCUMENTDIALOGCONTROLLER_H

#include <QWidget>
#include "Report/Unpaid/UnpaidDocumentTVModel.h"
#include "Report/Unpaid/UnpaidDocumentDialogView.h"
#include "Report/ReportDialogController.h"
class UnpaidDocumentDialogView;

class UnpaidDocumentDialogController : public ReportDialogController
{
    Q_OBJECT
protected:
    UnpaidDocumentDialogView *view;
    UnpaidDocumentTVModel *tvModel;

    void initNotPaidOnTimeFilterInModel(bool checked);

    void restoreTableState();
    void saveTableState();
public:
    UnpaidDocumentDialogController(QWidget *parent);

    void exec();

public slots:
    virtual void printReport() = 0;
    virtual void showOnlyNotPaidOnTime(bool checked) = 0;
};

#endif // UNPAIDDOCUMENTDIALOGCONTROLLER_H
