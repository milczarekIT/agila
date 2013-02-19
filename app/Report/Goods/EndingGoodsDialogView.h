#ifndef ENDINGGOODSDIALOGVIEW_H
#define ENDINGGOODSDIALOGVIEW_H

#include <QDoubleSpinBox>
#include "Report/ReportDialogView.h"
#include "Report/Goods/EndingGoodsDialogController.h"
class EndingGoodsDialogController;

class EndingGoodsDialogView : public ReportDialogView
{
    EndingGoodsDialogController *controller;

    QLabel *labelText;
    QDoubleSpinBox *spinBoxQuantity;

    void addComponents();
public:
    EndingGoodsDialogView(QWidget *parent, EndingGoodsDialogController *controller);

    void setTVModel(TVModel *model);

    QDoubleSpinBox *getSpinBoxQuantity();
};

#endif // ENDINGGOODSDIALOGVIEW_H
