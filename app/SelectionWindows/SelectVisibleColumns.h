#ifndef SELECTVISIBLECOLUMNS_H
#define SELECTVISIBLECOLUMNS_H

#include <QDialog>
#include <QTableView>
#include <QGridLayout>
#include <QButtonGroup>
#include <QGroupBox>
#include <QCheckBox>
#include <QHeaderView>
#include <QDebug>
#include "qmath.h"
#include "Components/ButtonBox.h"
#include "Other/Application/ApplicationManager.h"
#include "Other/Application/ModuleManager.h"

class SelectVisibleColumns : public QDialog
{
    Q_OBJECT
private:
    QTableView *table;
    QGridLayout *layout;
    QButtonGroup *checkBoxesGroup;
    QGroupBox *groupBox;
    ButtonBox *buttonBox;
    QList<QAbstractButton*> checkBoxList;

    void initView();
    void initConnections();

    bool isNextColumn(int nrModuloButtuonsInColumn);
    bool isTableWithIdColumn();

    QList<int> getSelectedColumns();
public:
    SelectVisibleColumns(QTableView *table, QWidget *parent = 0);



public slots:
    void exec();

signals:
    void selectedColumnsChanged(QList<int> selectedColumns);

private slots:
    void buttonSave();
};

#endif // SELECTVISIBLECOLUMNS_H
