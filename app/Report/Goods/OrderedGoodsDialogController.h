#ifndef ORDEREDGOODSDIALOGCONTROLLER_H
#define ORDEREDGOODSDIALOGCONTROLLER_H

#include "Report/ReportDialogController.h"
#include "Report/Goods/OrderedGoodsDialogView.h"
#include "Report/Goods/OrderedGoodsTVModel.h"
class OrderedGoodsDialogView;

class OrderedGoodsDialogController : public ReportDialogController
{
    QString type; // ZK or ZD
    OrderedGoodsDialogView *view;
    OrderedGoodsTVModel *tvModel;

    void restoreTableState();
    void saveTableState();
public:
    OrderedGoodsDialogController(QWidget *parent, QString type);
    ~OrderedGoodsDialogController();

    void exec();

public slots:
    void saveReport();
};

#endif // ORDEREDGOODSDIALOGCONTROLLER_H
