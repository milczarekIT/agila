#ifndef ORDEREDGOODSDIALOGVIEW_H
#define ORDEREDGOODSDIALOGVIEW_H

#include "Report/Goods/OrderedGoodsDialogController.h"
#include "Report/ReportDialogView.h"
class OrderedGoodsDialogController;

class OrderedGoodsDialogView : public ReportDialogView
{
    void addComponents();

    OrderedGoodsDialogController *controller;
public:
    OrderedGoodsDialogView(QWidget *parent, OrderedGoodsDialogController *controller);

    void setTVModel(TVModel *model);
};

#endif // ORDEREDGOODSDIALOGVIEW_H
