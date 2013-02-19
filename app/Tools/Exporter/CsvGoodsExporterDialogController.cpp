#include "CsvGoodsExporterDialogController.h"

CsvGoodsExporterDialogController::CsvGoodsExporterDialogController(QWidget *parent)
{
    defaultChecked << "Symbol" << "Nazwa" << "Grupa" << "VAT" << "j.m." << "Cena A netto" << "Cena A brutto";
    exporter = new CsvGoodsExporter();
    view = new CsvExporterDialogView(this, exporter->getAvailableHeader(), parent);
    view->setWindowTitle("Eksport towarów/usług do formatu csv");
    service = new GoodsService();


    fillTable();
    initColumnWidths();
    restoreTableState();
    selectCheckboxesWithVisibleColumns();
}

CsvGoodsExporterDialogController::~CsvGoodsExporterDialogController()
{
    saveTableState();
}

void  CsvGoodsExporterDialogController::fillTable() {
    goods = service->getGoods();

    QTableWidget *tableWidget = view->getTableWidget();
    Goods good;
    tableWidget->setRowCount(goods.size());
    for(int row = 0; row < goods.size(); row++) {
        good = goods[row];
        tableWidget->setItem(row, 0, new QTableWidgetItem(good.getSymbol()));
        tableWidget->setItem(row, 1, new QTableWidgetItem(good.getName()));
        tableWidget->setItem(row, 2, new QTableWidgetItem(good.getGoodsGroup().getName()));
        if(good.getType() == Goods::GOOD)
            tableWidget->setItem(row, 3, new QTableWidgetItem("Towar"));
        else if(good.getType() == Goods::SERVICE)
            tableWidget->setItem(row, 3, new QTableWidgetItem("Usługa"));
        if(good.getTax().getName().contains("zw."))
            tableWidget->setItem(row, 4, new QTableWidgetItem("zw."));
        else
            tableWidget->setItem(row, 4, new QTableWidgetItem(QVariant(good.getTax().getValue()).toString().append("%")));
        tableWidget->setItem(row, 5, new QTableWidgetItem(good.getUnit().getName()));
        tableWidget->setItem(row, 6, new QTableWidgetItem(good.getPriceNet(Price::A).toString()));
        tableWidget->setItem(row, 7, new QTableWidgetItem(good.getPriceGross(Price::A).toString()));
        tableWidget->setItem(row, 8, new QTableWidgetItem(good.getPriceNet(Price::B).toString()));
        tableWidget->setItem(row, 9, new QTableWidgetItem(good.getPriceGross(Price::B).toString()));
        tableWidget->setItem(row, 10, new QTableWidgetItem(good.getPriceNet(Price::C).toString()));
        tableWidget->setItem(row, 11, new QTableWidgetItem(good.getPriceGross(Price::C).toString()));
        tableWidget->setItem(row, 12, new QTableWidgetItem(good.getPriceNet(Price::MAG).toString()));
        tableWidget->setItem(row, 13, new QTableWidgetItem(good.getPriceGross(Price::MAG).toString()));
        tableWidget->setItem(row, 14, new QTableWidgetItem(good.getDescription()));
        tableWidget->setItem(row, 15, new QTableWidgetItem(good.getWeight()));
    }
}

void CsvGoodsExporterDialogController::initColumnWidths()
{
    QTableWidget *tableWidget = view->getTableWidget();
    tableWidget->setColumnWidth(0, 220);
    tableWidget->setColumnWidth(1, 220);
    tableWidget->setColumnWidth(2, 100);
    tableWidget->setColumnWidth(3, 90);
    tableWidget->setColumnWidth(4, 55);
    tableWidget->setColumnWidth(5, 45);
    tableWidget->setColumnWidth(6, 90);
    tableWidget->setColumnWidth(7, 90);
    tableWidget->setColumnWidth(8, 90);
    tableWidget->setColumnWidth(9, 90);
    tableWidget->setColumnWidth(10, 90);
    tableWidget->setColumnWidth(11, 90);
    tableWidget->setColumnWidth(12, 90);
    tableWidget->setColumnWidth(13, 90);
    tableWidget->setColumnWidth(14, 90);
    tableWidget->setColumnWidth(15, 90);
}

void CsvGoodsExporterDialogController::exportToFile() {

   QString filePath = QFileDialog::getSaveFileName(this, tr("Zapisz do pliku .csv"), QDir::homePath().append(QDir::separator()).append("kontrahenci.csv"), tr("Pliki CSV (*.csv)"));
    if(!filePath.isEmpty())
    {
        exporter->exportData(goods, filePath, getSelectedColumns());
    }

    view->close();
}

void CsvGoodsExporterDialogController::restoreTableState() {
    tableStateManager = new TableStateManager();
    QByteArray state = tableStateManager->getState("CSV_GOODS_EXPORTER");
    view->getTableWidget()->horizontalHeader()->restoreState(state);

    delete tableStateManager;
}

void CsvGoodsExporterDialogController::saveTableState() {
    tableStateManager = new TableStateManager();
    QByteArray state = view->getTableWidget()->horizontalHeader()->saveState();
    QByteArray oldState = tableStateManager->getState("CSV_GOODS_EXPORTER");
    if(state != oldState)
        tableStateManager->saveState("CSV_GOODS_EXPORTER", state);

    delete tableStateManager;
}
