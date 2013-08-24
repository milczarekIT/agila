#ifndef ENDINGGOODSDIALOGCONTROLLER_H
#define ENDINGGOODSDIALOGCONTROLLER_H

#include "Report/ReportDialogController.h"
#include "Report/Goods/ReportGoodsTVModel.h"
#include "Report/Goods/EndingGoodsDialogView.h"
class EndingGoodsDialogView;

class EndingGoodsDialogController : public ReportDialogController
{
    Q_OBJECT

    EndingGoodsDialogView *view;
    ReportGoodsTVModel *tvModel;

    void restoreTableState();
    void saveTableState();

public:
    EndingGoodsDialogController(QWidget *parent);
    ~EndingGoodsDialogController();

    void exec();

public slots:
    void saveReport();
    void quantityChanged(double value);
};

#endif // ENDINGGOODSDIALOGCONTROLLER_H
