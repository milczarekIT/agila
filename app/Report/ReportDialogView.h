#ifndef REPORTDIALOGVIEW_H
#define REPORTDIALOGVIEW_H

#include <QDialog>
#include <QGridLayout>
#include <QCheckBox>
#include <QTableView>
#include <QDialogButtonBox>
#include <QLabel>
#include <QLineEdit>
#include "Database/TVModel.h"

class ReportDialogView : public QDialog
{
    Q_OBJECT
protected:
    virtual void addComponents() = 0;

    QGridLayout *layout;
    QTableView *tableView;
    QLabel *labelValue;
    QLineEdit *lineValue;
    QDialogButtonBox* buttonBox;
public:
    ReportDialogView(QWidget *parent);

    virtual void setTVModel(TVModel *model) = 0;

    QTableView* getTableView();
    QLineEdit* getLineValue();
};

#endif // REPORTDIALOGVIEW_H
