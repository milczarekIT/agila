#ifndef MISSINGGOODSDIALOGCONTROLLER_H
#define MISSINGGOODSDIALOGCONTROLLER_H

#include "Report/ReportDialogController.h"
#include "Report/Goods/MissingGoodsDialogView.h"
#include "Report/Goods/ReportGoodsTVModel.h"
class MissingGoodsDialogView;

class MissingGoodsDialogController : public ReportDialogController
{
    MissingGoodsDialogView *view;
    ReportGoodsTVModel *tvModel;

    void restoreTableState();
    void saveTableState();

public:
    MissingGoodsDialogController(QWidget *parent);
    ~MissingGoodsDialogController();

    void exec();

public slots:
    void printReport();
};

#endif // MISSINGGOODSDIALOGCONTROLLER_H
