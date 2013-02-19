#include "CsvContractorExporterDialogController.h"

CsvContractorExporterDialogController::CsvContractorExporterDialogController(QWidget *parent)
{
    defaultChecked << "Symbol" << "Nazwa" << "Grupa" << "Kod pocztowy" << "Miejscowość" << "Adres";
    exporter = new CsvContractorExporter();
    view = new CsvExporterDialogView(this, exporter->getAvailableHeader(), parent);
    view->setWindowTitle("Eksport kontrahentów do formatu csv");
    service = new ContractorService();

    fillTable();
    initColumnWidths();

    restoreTableState();
    selectCheckboxesWithVisibleColumns();
}

CsvContractorExporterDialogController::~CsvContractorExporterDialogController()
{
    saveTableState();
}

void  CsvContractorExporterDialogController::fillTable() {
    contractors = service->getContractors();

    QTableWidget *tableWidget = view->getTableWidget();
    Contractor contractor;
    tableWidget->setRowCount(contractors.size());
    for(int row = 0; row < contractors.size(); row++) {
        contractor = contractors[row];
        tableWidget->setItem(row, 0, new QTableWidgetItem(contractor.getSymbol()));
        tableWidget->setItem(row, 1, new QTableWidgetItem(contractor.getName()));
        tableWidget->setItem(row, 2, new QTableWidgetItem(contractor.getContractorGroup().getName()));
        tableWidget->setItem(row, 3, new QTableWidgetItem(contractor.getPostcode()));
        tableWidget->setItem(row, 4, new QTableWidgetItem(contractor.getCity()));
        tableWidget->setItem(row, 5, new QTableWidgetItem(contractor.getAddress()));
        tableWidget->setItem(row, 6, new QTableWidgetItem(contractor.getDefultPhone()));
        tableWidget->setItem(row, 7, new QTableWidgetItem(contractor.getNip()));
        tableWidget->setItem(row, 8, new QTableWidgetItem(contractor.getEmail()));
        tableWidget->setItem(row, 9, new QTableWidgetItem(contractor.getWebsite()));
        tableWidget->setItem(row, 10, new QTableWidgetItem(contractor.getDiscount()));
    }
}

void CsvContractorExporterDialogController::initColumnWidths() {

    QTableWidget *tableWidget = view->getTableWidget();
    tableWidget->setColumnWidth(0, 200);
    tableWidget->setColumnWidth(1, 200);
    tableWidget->setColumnWidth(2, 130);
    tableWidget->setColumnWidth(3, 90);
    tableWidget->setColumnWidth(4, 110);
    tableWidget->setColumnWidth(5, 140);
    tableWidget->setColumnWidth(6, 100);
    tableWidget->setColumnWidth(7, 100);
    tableWidget->setColumnWidth(8, 100);
    tableWidget->setColumnWidth(9, 100);
    tableWidget->setColumnWidth(10, 100);
}

void CsvContractorExporterDialogController::exportToFile() {

   QString filePath = QFileDialog::getSaveFileName(this, tr("Zapisz do pliku .csv"), QDir::homePath().append(QDir::separator()).append("kontrahenci.csv"), tr("Pliki CSV (*.csv)"));
    if(!filePath.isEmpty())
    {
        exporter->exportData(contractors, filePath, getSelectedColumns());
    }

    view->close();
}

void CsvContractorExporterDialogController::restoreTableState() {
    tableStateManager = new TableStateManager();
    QByteArray state = tableStateManager->getState("CSV_CONTRACTOR_EXPORTER");
    view->getTableWidget()->horizontalHeader()->restoreState(state);

    delete tableStateManager;
}

void CsvContractorExporterDialogController::saveTableState() {
    tableStateManager = new TableStateManager();
    QByteArray state = view->getTableWidget()->horizontalHeader()->saveState();
    QByteArray oldState = tableStateManager->getState("CSV_CONTRACTOR_EXPORTER");
    if(state != oldState)
        tableStateManager->saveState("CSV_CONTRACTOR_EXPORTER", state);

    delete tableStateManager;
}
