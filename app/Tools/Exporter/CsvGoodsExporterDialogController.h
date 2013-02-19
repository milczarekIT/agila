#ifndef CSVGOODSEXPORTERDIALOGCONTROLLER_H
#define CSVGOODSEXPORTERDIALOGCONTROLLER_H

#include "Goods/GoodsService.h"
#include "Tools/Exporter/CsvContractorExporterDialogController.h"
#include "Tools/Exporter/CsvGoodsExporter.h"
#include "Other/ITableStateManager.h"

class CsvGoodsExporterDialogController : public CsvExporterDialogController, public ITableStateManager
{
private:
    CsvGoodsExporter *exporter;
    GoodsService *service;
    QVector<Goods> goods;

    void fillTable();
    void initColumnWidths();

    void restoreTableState();
    void saveTableState();
public:
    CsvGoodsExporterDialogController(QWidget *parent = 0);
    ~CsvGoodsExporterDialogController();

public slots:
    void exportToFile();

};

#endif // CSVGOODSEXPORTERDIALOGCONTROLLER_H
