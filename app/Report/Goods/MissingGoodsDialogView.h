#ifndef MISSINGGOODSDIALOGVIEW_H
#define MISSINGGOODSDIALOGVIEW_H

#include "Report/ReportDialogView.h"
#include "Report/Goods/MissingGoodsDialogController.h"
class MissingGoodsDialogController;

class MissingGoodsDialogView : public ReportDialogView
{
    void addComponents();

    MissingGoodsDialogController *controller;
public:
    MissingGoodsDialogView(QWidget *parent, MissingGoodsDialogController *controller);

    void setTVModel(TVModel *model);
};

#endif // MISSINGGOODSDIALOGVIEW_H
