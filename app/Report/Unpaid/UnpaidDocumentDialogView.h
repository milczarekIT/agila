#ifndef UNPAIDDOCUMENTDIALOGVIEW_H
#define UNPAIDDOCUMENTDIALOGVIEW_H

#include <QDialog>
#include <QTableView>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QDialogButtonBox>
#include <QCheckBox>
#include "Report/Unpaid/UnpaidDocumentDialogController.h"
#include "Database/TVModel.h"
class UnpaidDocumentDialogController;

class UnpaidDocumentDialogView : public QDialog
{
    Q_OBJECT
private:
    UnpaidDocumentDialogController *controller;

    QTableView *tableView;
    QLineEdit *lineValue;
    QLabel *labelValue;
    QGridLayout *layout;
    QDialogButtonBox *buttonBox;
    QCheckBox *checkBoxOnlyNotPaidOnTime;

    void addComponents();
public:
    UnpaidDocumentDialogView(QWidget *parent, UnpaidDocumentDialogController *controller);
    ~UnpaidDocumentDialogView();

    void setTVModel(TVModel *tvModel);
    void initTVColumnWidhts();

    QLineEdit* getLineValue();
    QTableView *getTableView();
};

#endif // UNPAIDSALEDOCUMENTDIALOGVIEW_H
