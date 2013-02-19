#ifndef TOPGOODSDIALOGVIEW_H
#define TOPGOODSDIALOGVIEW_H

#include <QSpinBox>
#include "Report/Goods/TopGoodsDialogController.h"
#include "Report/ReportDialogView.h"
#include "Components/DateEdit.h"
class TopGoodsDialogController;

class TopGoodsDialogView : public ReportDialogView
{
    QSpinBox *spinBoxListLimit;
    DateEdit *dateEditFrom;
    DateEdit *dateEditTo;

    void addComponents();

    TopGoodsDialogController *controller;
public:
    TopGoodsDialogView(QWidget *parent, TopGoodsDialogController *controller);

    void setTVModel(TVModel *model);

    QSpinBox *getSpinBoxListLimit();
    DateEdit *getDateEditFrom();
    DateEdit *getDateEditTo();

};

#endif // TOPGOODSDIALOGVIEW_H
