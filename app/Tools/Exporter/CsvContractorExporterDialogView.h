#ifndef CSVCONTRACTOREXPORTERDIALOGVIEW_H
#define CSVCONTRACTOREXPORTERDIALOGVIEW_H

#include <QDialog>
#include <QGroupBox>
#include <QButtonGroup>
#include <QGridLayout>
#include <QTableWidget>
#include <QDialogButtonBox>
#include <QHeaderView>
#include <QCheckBox>
#include "Tools/Exporter/CsvContractorExporterDialogController.h"
class CsvContractorExporterDialogController;

class CsvContractorExporterDialogView : public QDialog
{

public:
    CsvContractorExporterDialogView(CsvContractorExporterDialogController *controller, QStringList availableColumns, QWidget *parent = 0);

    QButtonGroup *getCheckBoxesGroup();
    QList<QAbstractButton*> getCheckBoxList();
    QTableWidget *getTableWidget();
};

#endif // CSVCONTRACTOREXPORTERDIALOGVIEW_H
