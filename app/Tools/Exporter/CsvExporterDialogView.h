#ifndef CSVEXPORTERDIALOGVIEW_H
#define CSVEXPORTERDIALOGVIEW_H

#include <QDialog>
#include <QGroupBox>
#include <QButtonGroup>
#include <QGridLayout>
#include <QCheckBox>
#include <QDebug>
#include <QHeaderView>
#include <QTableWidget>
#include <QDialogButtonBox>
#include <qmath.h>
#include "Tools/Exporter/CsvExporterDialogController.h"
class CsvExporterDialogController;

class CsvExporterDialogView : public QDialog
{
protected:
    CsvExporterDialogController *controller;

    QGroupBox *groupBox;
    QButtonGroup *checkBoxesGroup;
    QList<QAbstractButton*> checkBoxList;
    QStringList availableColumns;
    QGridLayout *layout;
    QTableWidget *tableWidget;
    QDialogButtonBox *buttonBox;

    void initComponents();
    void initCheckboxes();
    void initTable();
    void initButtonBox();
    void initConnections();
public:
    CsvExporterDialogView(CsvExporterDialogController *controller, QStringList availableColumns, QWidget *parent);

    QButtonGroup *getCheckBoxesGroup();
    QList<QAbstractButton*> getCheckBoxList();
    QTableWidget *getTableWidget();
};

#endif // CSVEXPORTERDIALOGVIEW_H
