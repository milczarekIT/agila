#include "CsvExporterDialogController.h"

CsvExporterDialogController::CsvExporterDialogController()
{
}

void CsvExporterDialogController::exec()
{
    view->exec();
}

QStringList CsvExporterDialogController::getSelectedColumns() {
    QStringList selectedColumns;
    QList<QAbstractButton*> checkBoxList = view->getCheckBoxList();
    foreach(QAbstractButton  *button, checkBoxList) {
        if(button->isChecked())
            selectedColumns << button->text();
    }
    return selectedColumns;
}

void CsvExporterDialogController::setTableColumnHidden(int column, bool hide) {
    view->getTableWidget()->setColumnHidden(column, hide);
}

QStringList CsvExporterDialogController::getDefaultChecked() {
    return defaultChecked;
}

void CsvExporterDialogController::initColumnWidths() {
    for(int i = 0; i < view->getTableWidget()->columnCount(); i++)
        view->getTableWidget()->setColumnWidth(i, 100);
}

void CsvExporterDialogController::checkBoxClicked(int id)
{
    QAbstractButton *checkbox = view->getCheckBoxesGroup()->button(id);
    if(checkbox->isChecked())
        setTableColumnHidden(id, false);
    else
        setTableColumnHidden(id, true);
}

void CsvExporterDialogController::selectCheckboxesWithVisibleColumns()
{
    QTableWidget *tableWidget = view->getTableWidget();
    QList<QAbstractButton*> checkBoxList = view->getCheckBoxList();
    for(int i = 0; i < tableWidget->columnCount(); i++)
    {
        if(tableWidget->isColumnHidden(i))
            checkBoxList.at(i)->setChecked(false);
        else
            checkBoxList.at(i)->setChecked(true);
    }

}

