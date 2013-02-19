#ifndef CSVEXPORTERDIALOGCONTROLLER_H
#define CSVEXPORTERDIALOGCONTROLLER_H

#include <QWidget>
#include <QAbstractButton>
#include <QFileDialog>
#include "Tools/Exporter/CsvExporterDialogView.h"
class CsvExporterDialogView;

class CsvExporterDialogController : public QWidget
{
    Q_OBJECT
protected:
    CsvExporterDialogView *view;
    QStringList defaultChecked;

    void setTableColumnHidden(int column, bool hide);
    QStringList getSelectedColumns();
    void selectCheckboxesWithVisibleColumns();
    virtual void fillTable() = 0;
    virtual void initColumnWidths();
public:
    CsvExporterDialogController();

    void exec();

    QStringList getDefaultChecked();

public slots:
    void checkBoxClicked(int id);
    virtual void exportToFile() = 0;
};

#endif // CSVEXPORTERDIALOGCONTROLLER_H
