#ifndef TOPCONTRACTORSDIALOGVIEW_H
#define TOPCONTRACTORSDIALOGVIEW_H

#include <QSpinBox>
#include "Report/ReportDialogView.h"
#include "Components/DateEdit.h"
#include "Report/Contractor/TopContractorsDialogController.h"
class TopContractorsDialogController;

class TopContractorsDialogView : public ReportDialogView
{
    TopContractorsDialogController *controller;

    QSpinBox *spinBoxListLimit;
    DateEdit *dateEditFrom;
    DateEdit *dateEditTo;

    void addComponents();

public:
    TopContractorsDialogView(QWidget *parent, TopContractorsDialogController *controller);

    void setTVModel(TVModel *model);

    QSpinBox *getSpinBoxListLimit();
    DateEdit *getDateEditFrom();
    DateEdit *getDateEditTo();
};

#endif // TOPCONTRACTORSDIALOGVIEW_H
