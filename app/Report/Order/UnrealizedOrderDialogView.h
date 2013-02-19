#ifndef UNREALIZEDORDERDIALOGVIEW_H
#define UNREALIZEDORDERDIALOGVIEW_H

#include "Report/ReportDialogView.h"
#include "Report/Order/UnrealizedOrderDialogController.h"
class UnrealizedOrderDialogController;

class UnrealizedOrderDialogView : public ReportDialogView
{
    void addComponents();

    UnrealizedOrderDialogController *controller;
public:
    UnrealizedOrderDialogView(QWidget *parent, UnrealizedOrderDialogController *controller);

    void setTVModel(TVModel *model);
};

#endif // UNREALIZEDORDERDIALOGVIEW_H
