#ifndef UNPAIDSALEDOCUMENTDIALOGCONTROLLER_H
#define UNPAIDSALEDOCUMENTDIALOGCONTROLLER_H

#include "Report/Unpaid/UnpaidDocumentDialogView.h"
#include "Report/Unpaid/UnpaidDocumentTVModel.h"
#include "Report/Report.h"
class UnpaidDocumentDialogView;

class UnpaidSaleDocumentDialogController : public UnpaidDocumentDialogController
{
public:
    UnpaidSaleDocumentDialogController(QWidget *parent);
    ~UnpaidSaleDocumentDialogController();

public slots:
    void showOnlyNotPaidOnTime(bool checked);
    void saveReport();
};

#endif // UNPAIDSALEDOCUMENTDIALOGCONTROLLER_H
