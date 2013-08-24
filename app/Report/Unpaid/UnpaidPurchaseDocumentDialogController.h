#ifndef UNPAIDPURCHASEDOCUMENTDIALOGCONTROLLER_H
#define UNPAIDPURCHASEDOCUMENTDIALOGCONTROLLER_H

#include <QWidget>
#include "Report/Unpaid/UnpaidDocumentDialogView.h"
#include "Report/Unpaid/UnpaidDocumentDialogController.h"
class UnpaidDocumentDialogView;

class UnpaidPurchaseDocumentDialogController : public UnpaidDocumentDialogController
{
public:
    UnpaidPurchaseDocumentDialogController(QWidget *parent);
    ~UnpaidPurchaseDocumentDialogController();

public slots:
    void showOnlyNotPaidOnTime(bool checked);
    void saveReport();
};

#endif // UNPAIDPURCHASEDOCUMENTDIALOGCONTROLLER_H
