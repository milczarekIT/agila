#ifndef INVENTORYDIALOGVIEW_H
#define INVENTORYDIALOGVIEW_H

#include <QHeaderView>
#include "Database/TVModel.h"
#include "Report/ReportDialogView.h"

class InventoryDialogView : public ReportDialogView
{
protected:
    QCheckBox *checkBoxShowWithZeroQuantity;

    void addComponents();
public:
    InventoryDialogView(QWidget *parent);

    QCheckBox *getCheckBoxShowWithZeroQuantity();
};

#endif // INVETORYDIALOGVIEW_H
