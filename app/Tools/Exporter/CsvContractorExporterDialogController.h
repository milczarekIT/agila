#ifndef CSVCONTRACTOREXPORTERDIALOGCONTROLLER_H
#define CSVCONTRACTOREXPORTERDIALOGCONTROLLER_H

#include "Tools/Exporter/CsvContractorExporter.h"
#include "Tools/Exporter/CsvExporterDialogView.h"
#include "Tools/Exporter/CsvExporterDialogController.h"
#include "Other/ITableStateManager.h"
class CsvExporterDialogView;

class CsvContractorExporterDialogController : public CsvExporterDialogController, public ITableStateManager
{
private:
    CsvContractorExporter *exporter;
    ContractorService *service;
    QVector<Contractor> contractors;

    void fillTable();
    void initColumnWidths();

    void restoreTableState();
    void saveTableState();
public:
    CsvContractorExporterDialogController(QWidget *parent = 0);
    ~CsvContractorExporterDialogController();

public slots:
    void exportToFile();
};

#endif // CSVCONTRACTOREXPORTERDIALOGCONTROLLER_H
